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
	if (input_result != -1)
	{
		set_info(info, av);
		*builtin_result = identify_builtin(info);
		if (*builtin_result == -1)
		{
			identify_command(info);
		}
	}
	else if (check_interactive(info))
	{
		putchar('\n');
	}
	release_info(info, 0);
}

/**
 * hist_buf - Processes a history buffer, splitting it into lines
 * and building a history list.
 * @buffer: Pointer to the buffer containing the history data.
 * @size: Size of the buffer.
 * @last: Pointer to the variable storing the index
 * of the last processed character.
 * @lncnt: Pointer to the variable storing the current line count.
 * @hist: Pointer to the history list.
 *
 * This function processes the input buffer,
 * splitting it into lines based on newline
 * characters and building a history list.
 * It updates the 'last' index and increments
 * the 'linecount' accordingly.
 */
void hist_buf(char *buffer, size_t size, int *last, int *lncnt, list_t *hist)
{
	int i = 0;

	while (i < size)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			build_history_list(buffer + *last, (*linecount)++, history);
			*last = i + 1;
		}
		i++;
	}

	if (*last != size)
		build_history_list(buffer + *last, (*linecount)++, history);
}
