#include "shell.h"
void initialize_input(Input *input)
{
	input->buffer = NULL;
	input->length = 0;
	input->command_buffer = NULL;
	input->linecount_flag = 0;
	input->histcount = 0;
	input->i = 0;
}
void free_input(Input *input)
{
	int i;
	free(input->buffer);
	/*Assuming the command buffer is dynamically allocated*/
	for (i = 0; i < input->histcount; i++)
	{
		free(input->command_buffer[i]);
	}
	free(input->command_buffer);
}
ssize_t input_buf(Input *input, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(input, buf, &len_p);
#endif

		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			input->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(input, *buf, input->histcount++);

			/* Check for command chain */
			if (_strchr(*buf, ';'))
			{
				*len = r;
				input->command_buffer = buf;
			}
		}
	}
	return r;
}

ssize_t get_input(Input *input)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(input->buffer), *p;

	putchar(BUF_FLUSH);
	r = input_buf(input, &buf, &len);

	if (r == -1)
	{
		return -1;
	}

	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(input, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(input, buf, &j))
			{
				break;
			}
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			input->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return strlen(p);
	}
	*buf_p = buf;
	return r;
}

ssize_t read_buf(Input *input, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
	{
		return 0;
	}

	r = read(input->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
	{
		*i = r;
	}

	return r;
}
