#include "shell.h"

/**
 * history_handler - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @input: Input struct
 * Return: Always 0
 */
int history_handler(Input *input)
{
	print_list(input->history);
	return (0);
}

/**
 * alias_handler - mimics the alias builtin (man alias)
 * @input: Input struct
 * Return: Always 0
 */
int alias_handler(Input *input)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;


	if (input->argc == 1)
	{
		node = input->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; input->argv[i]; i++)
	{
		p = _strchr(input->argv[i], '=');
		if (p)
			set_alias(input, input->argv[i]);
		else
			print_alias(node_starts_with(input->alias, input->argv[i], '='));
	}

	return (0);
}

/**
 * fork_cmd - forks an exec thread to run cmd
 * @input: the Input struct
 *
 * Return: void
 */
void execute_command(Input *input)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(input->path, input->argv, input->environment) == -1)
		{
			perror("Error:");
			free(input);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(input->status));
		if (WIFEXITED(input->status))
		{
			input->status = WEXITSTATUS(input->status);
			if (input->status == 126)
				fprintf(stderr, "Permission denied\n");
		}
	}
}
