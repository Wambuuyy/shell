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
ssize_t get_input(Input *input, info_t *info)
{
	ssize_t r = 0;
	char **buf_p = &(info->arg);

	putchar(BUF_FLUSH);
	r = input_buf(info, &(input->buffer), &(input->length));
	if (r == -1) /* EOF */
		return (-1);
	if (input->length) /* we have commands left in the chain buffer */
	{
		size_t j = input->i; /* init new iterator to current buf position */
		char *p = input->buffer + input->i; /* get pointer for return */

		check_chain(info, input->buffer, &j, input->i, input->length);
		while (j < input->length) /* iterate to semicolon or end */
		{
			if (is_chain(info, input->buffer, &j))
				break;
			j++;
		}

		input->i = j + 1; /* increment past nulled ';'' */
		if (input->i >= input->length) /* reached end of buffer? */
		{
			input->i = input->length = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = input->buffer; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}
