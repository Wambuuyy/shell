#include "shell.h"

void clear_info(int *info)
{
	info[0] = NULL;
	info[1] = NULL;
	info[2] = NULL;
	/* Freeing allocated memory if necessary
	 * Example: if info[3] contains a dynamically allocated string
	 * free(info[3]);
	 * You may need to add more logic based on the actual content and structure of your info array.
	 * */
}

void print_prompt(int *info)
{
	if (check_interactive(info))
	{
		printf("$ ");
		fflush(stdout);
	}
}
int check_interactive(int readfd)
{
	return (isatty(STDIN_FILENO) && readfd <= 2) ? INTERACTIVE_FLAG : NON_INTERACTIVE_FLAG;
}

void process_input(int *info, char **av, ssize_t input_result, int *builtin_result)
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
