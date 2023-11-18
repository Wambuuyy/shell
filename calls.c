#include "shell.h"

/**
 * print_prompt - Prints a prompt ('$ ') if the environment is interactive.
 * @input: Pointer to an integer.
 */
void print_prompt(Input *input)
{
	if (check_interactive(input))
	{
		printf("$ ");
		fflush(stdout);
	}
}

/**
 * check_interactive - Checks if the program is running in interactive mode.
 * @input: Integer representing the file descriptor.
 *
 * Return: INTERACTIVE_FLAG if interactive, NON_INTERACTIVE_FLAG otherwise.
 */
int check_interactive(Input *input)
{
	return ((isatty(STDIN_FILENO) && input->readfd <= 2) ?
		INTERACTIVE_FLAG : NON_INTERACTIVE_FLAG);
}

/**
 * process_input - Processes input based on the results
 * of a previous input operation.
 * @input: Pointer to an integer.
 * @av: Array of strings representing arguments.
 * @result: Result of the input operation.
 * @bresults: Pointer to an integer to store
 * the result of identifying a built-in command.
 */
void process_input(Input *input, char **av, ssize_t result, int *bresults)
{
	if (result != -1)
	{
		set_info(input, av[0]);
		*bresults = identify_builtin(input);
		if (*bresults == -1)
		{
			identify_command(input);
		}
	}
	else if (check_interactive(input))
	{
		putchar('\n');
	}
	release_info(input, 0);
}

/**
 * hist_buf - Processes a history buffer, splitting it into lines
 * and building a history list.
 * input: Input struct.
 * This function processes the input buffer,
 * splitting it into lines based on newline
 * characters and building a history list.
 * It updates the 'last' index and increments
 * the 'linecount' accordingly.
 */
void hist_buf(Input *input, size_t size, char **buffer, int *last)
{
	size_t i = 0;

	while (i < size)
	{
		if (strcmp(buffer[i], "\n") == 0)
		{
			buffer[i] = '\0';
			build_hist_list(input);
			*last = i + 1;
		}
		i++;
	}

	if (*last != (int)size)
		build_hist_list(input);
}
