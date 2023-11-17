#include "shell.h"
/**
 * identify_command - Identifies and processes the command from the input.
 * @input: A pointer to the Input structure containing the command information.
 *
 * Description:
 * This function examines the command in the input buffer and takes appropriate
 * actions, such as executing external commands or handling built-in commands.
 *
 * Return: An integer status code indicating the success or failure of
 * the identification process.
 */
int identify_command(Input *input)
{
	char *path = NULL;
	size_t i;

	if (input->buffer[0] == '\n')
	{
		return;
	}

	for (i = 0, k = 0; input->buffer[i]; i++)
	{
		if (!strchr(" \t\n", input->buffer[i]))
			k++;
	}

	if (!k)
		return;

	path = getenv("PATH");

	if (path)
		path = find_path(input->buffer, path, input->argv[0]);

	if (path)
		execute_command(path, input->argv);
	else
	{
		if ((isatty(STDIN_FILENO) || getenv("PATH") || input->buffer[0] == '/') &&
				is_cmd(input->buffer, input->argv[0]))
			execute_command(input->buffer, input->argv);
		else
		{
			fprintf(stderr, "Error: Command not found\n");
			exit(127);
		}
	}
}

/**
 * identify_builtin - Identifies and processes built-in
 * commands from the input.
 * @input: A pointer to the Input structure containing
 * the command information.
 * Description:
 * This function checks if the command in the
 * input buffer corresponds to
 * a built-in command and executes the corresponding action.
 *
 * Return: An integer status code indicating the success or failure of
 * the identification process.
 */
int identify_builtin(Input *input)
{
	const char *builtin_types[MAX_BUILTIN_TYPES] = {
		"exit",
		"env",
		"history",
		"setenv",
		"unsetenv",
		"cd",
		"alias",
		"help"
	};


	int (*builtin_funcs[MAX_BUILTIN_TYPES])(char **) = {
		exit_handler,
		env_handler,
		history_handler,
		setenv_handler,
		unsetenv_handler,
		cd_handler,
		alias_handler,
		help_handler
	};


	for (int i = 0; i < MAX_BUILTIN_TYPES; i++)
	{
		if (strcmp(input->buffer, builtin_types[i]) == 0)
		{
			input->status = builtin_funcs[i](input->argv);
			return (i);
		}
	}
}
