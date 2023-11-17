#include "shell.h"
/**
 * initialize_input - Initializes an Input structure with default values.
 * @input: Pointer to the Input structure to be initialized.
 *
 * This function sets the initial values for an
 * Input structure, preparing it for
 * input processing. It ensures proper initialization of
 * members and allocation
 * of necessary resources.
 */
void initialize_input(Input *input)
{
	input->buffer = NULL;
	input->length = 0;
	input->command_buffer = NULL;
	input->linecount_flag = 0;
	input->histcount = 0;
	input->i = 0;
}

/**
 * free_input - Frees resources allocated for an Input struct
 * @input: Pointer to the Input structure to be freed.
 *
 * This function releases any dynamically allocated memory
 * associated with an Input
 * structure, ensuring proper cleanup to prevent memory leaks
 */
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

/**
 * input_buf - Reads input from the user into a dynamically allocated buffer.
 * @input: Pointer to the Input structure.
 * @buf: Pointer to the buffer where the input will be stored.
 * @len: Pointer to the size_t variable to store the
 * length of the input.
 *
 * This function reads input from the user,
 * dynamically allocating memory for the
 * buffer to store the input. The length of the input
 * and the allocated buffer are
 * returned through the len and buf parameters, respectively.
 * Return: The number of characters read, or -1 on failure.
 */
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
	return (r);
}

/**
 * get_input - Obtains input from the user and updates
 * the Input structure.
 * @input: Pointer to the Input structure.
 *
 * This function prompts the user for input,
 * updates the Input structure with the
 * provided input, and returns the length of the input.
 * It ensures proper handling
 * of interactive and non-interactive input modes.
 *
 * Return: The length of the input, or -1 on failure.
 */

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
		return (-1);
	}

	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(input, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(input, buf, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= len)
		{
			i = len = 0;
			input->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buf - Reads characters from the input buffer
 * into a specified buffer.
 * @input: Pointer to the Input structure.
 * @buf: Pointer to the buffer where characters will be stored.
 * @i: Pointer to the size_t variable representing
 * the current index in the buffer.
 *
 * This function reads characters from the input buffer,
 * updating the specified buffer
 * and index accordingly. It is used for processing
 * input character by character.
 *
 * Return: The number of characters read, or -1 on failure.
 */
ssize_t read_buf(Input *input, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
	{
		return (0);
	}

	r = read(input->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
	{
		*i = r;
	}

	return (r);
}
