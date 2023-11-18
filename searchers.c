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
	size_t i, k;

	if (input->buffer[0] == '\n')
	{
		return (0);
	}

	for (i = 0, k = 0; input->buffer[i]; i++)
	{
		if (!strchr(" \t\n", input->buffer[i]))
			k++;
	}

	if (!k)
		return (0);

	path = getenv("PATH");

	if (path)
		path = find_path(input, path, input->argv[0]);

	if (path)
	{
		execute_command(input);
		return (0);
	}
	else
	{
		if ((isatty(STDIN_FILENO) || getenv("PATH") || input->buffer[0] == '/') &&
				is_cmd(input, input->argv[0]))
		{
			execute_command(input);
			return (0);
		}
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
 * Description:
 * This function checks if the command in the input buffer
 * corresponds to a built-in command and executes the corresponding action.
 *
 * Return: An integer status code indicating the success
 * or failure of the identification process.
 */
int identify_builtin(Input *input)
{
	int i, builtreturn = -1;

	struct Builtins builtins[] = {
		{"exit", exit_handler},
		{"env", env_handler},
		{"history", history_handler},
		{"setenv", setenv_handler},
		{"unsetenv", unsetenv_handler},
		{"cd", cd_handler},
		{"alias", alias_handler},
		{"help", help_handler},
		{NULL, NULL}
	};

	for (i = 0; builtins[i].command != NULL; i++)
	{
		if (strcmp(input->buffer, builtins[i].command) == 0)
		{
			input->status = builtins[i].handler(input);
			builtreturn = i;
			break;
		}
	}

	return (builtreturn);
}
