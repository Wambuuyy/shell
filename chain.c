#include "shell.h"

/**
 * is_chain - Tests if the current character in the buffer is a chain delimiter
 * @input: Input struct
 * @buf: Character buffer
 * @p: Address of the current position in buf
 *
 * Return: 1 if a chain delimiter, 0 otherwise
 */
int is_chain(Input *input, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		input->buffer_type = COMMAND_OR;
	} else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		input->buffer_type = COMMAND_AND;
	} else if (buf[j] == ';')
	{
		buf[j] = 0;
		input->buffer_type = COMMAND_CHAIN;
	} else
	{
		return (0);
	}

	*p = j;
	return (1);
}

/**
 * check_chain - Checks if we should continue chaining based on the last status
 * @input: Input struct
 * @buf: Character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void check_chain(Input *input, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (input->buffer_type == COMMAND_AND)
	{
		if (input->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	if (input->buffer_type == COMMAND_OR)
	{
		if (!input->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


/**
 * setenv_handler - Initialize a new environment variable or modify an existing one
 * @input: Structure containing potential arguments and other shell information.
 * Return: Always 0
 */
int setenv_handler(Input *input)
{
	if (input->argc != 3)
	{
		fprintf(stderr, "Error: Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(input, input->argv[1], input->argv[2]) == 0)
	{
		return (0);
	}
	return (1);
}

/**
 * unsetenv_handler - Remove an environment variable
 * @input: Structure containing potential arguments and other shell information.
 * Return: Always 0
 */
int unsetenv_handler(Input *input)
{
	int i;

	if (input->argc < 2)
	{
		fprintf(stderr, "Error: Too few arguments\n");
		return (1);
	}

	for (i = 1; i <= input->argc; i++)
	{
		_unsetenv(input, input->argv[i]);
	}

	return (0);
}
/**
 * env_handler - Display the environment variables.
 * @input: Structure containing potential arguments and other shell information.
 */
int env_handler(Input *input)
{
	if (input->env == NULL)
	{
		fprintf(stderr, "Error: Environment variable list is NULL\n");
		return (1);
	}
	print_list(input->env);
	return (0);
}
