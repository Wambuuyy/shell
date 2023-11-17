#include "shell.h"

/**
 * print_prompt - Prints a prompt ('$ ') if the environment is interactive.
 * @info: Pointer to an integer.
 */
void print_prompt(int *info)
{
	if (check_interactive(info))
	{
		printf("$ ");
		fflush(stdout);
	}
}

/**
 * check_interactive - Checks if the program is running in interactive mode.
 * @readfd: Integer representing the file descriptor.
 *
 * Return: INTERACTIVE_FLAG if interactive, NON_INTERACTIVE_FLAG otherwise.
 */
int check_interactive(int readfd)
{
	return ((isatty(STDIN_FILENO) && readfd <= 2) ?
		INTERACTIVE_FLAG : NON_INTERACTIVE_FLAG)
}

/**
 * process_input - Processes input based on the results
 * of a previous input operation.
 * @info: Pointer to an integer.
 * @av: Array of strings representing arguments.
 * @input_result: Result of the input operation.
 * @builtin_result: Pointer to an integer to store
 * the result of identifying a built-in command.
 */
void process_input(Input *input, char **av, ssize_t input_result, int *builtin_result)
{
	if (input_result != -1)
	{
		set_info(info, av);
		*builtin_result = identify_builtin(info);
		if (*builtin_result == -1)
		{
			identify_command(info);
		}
	}
	else if (is_interactive(info))
	{
		putchar('\n');
	}
	release_info(info, 0);
}
