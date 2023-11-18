#include "shell.h"

/**
 * clear_info - Initializes Input fields to default values.
 * @input: Pointer to the Input structure.
 */
void clear_info(Input *input)
{
	input->buffer = NULL;
	input->command_buffer = NULL;
	input->argc = 0;
}

/**
 * print_list - Prints the elements of a string array.
 * @list: The string array to be printed.
 */
void print_list(list_t *list)
{
	while(list != NULL)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
}

/**
 * set_info - Initializes Input fields based on provided arguments.
 * @input: Pointer to the Input structure.
 * @filename: Filename field.
 * @arg: Argument field.
 */
void set_info(Input *input, char *arg)
{
	int i = 0;

	input->buffer = arg;
	if (arg)
	{
		input->command_buffer = custom_strtok(arg, " \t");
		if (!input->command_buffer) {
			input->command_buffer = malloc(sizeof(char *) * 2);
			if (input->command_buffer) {
				input->command_buffer[0] = strdup(arg);
				input->command_buffer[1] = NULL;
			}
		}
		for (i = 0; input->command_buffer && input->command_buffer[i]; i++)
			;
		input->argc = i;


		replace_alias(input);
		replace_vars(input);
	}
}

/**
 * release_info - Frees allocated memory in Input fields.
 * @input: Pointer to the Input structure.
 * @all: True if freeing all fields.
 */
void release_info(Input *input, int all)
{
	int i;

	for (i = 0; i < input->argc; ++i)
	{
		free(input->command_buffer[i]);
		input->command_buffer[i] = NULL;
	}

	free(input->command_buffer);
	input->command_buffer = NULL;
	
	if (all)
	{
		bfree((void **)&(input->buffer));
		if (input->readfd > 2)
			close(input->readfd);
		putchar(BUF_FLUSH);
		ffree(input->env);
		input->env = NULL;
	}
}
