#include "shell.h"

/**
 * build_hist_list - builds a history list from the input buffer
 * @input: the input buffer containing the command
 *
 * Return: 1 on success, 0 on failure
 */
int build_hist_list(Input *input)
{
	list_t *node = NULL;

	if (input->history)
		node = input->history;
	appendnode_end(&node, input->buffer, input->linecount);
	if (!input->history)
		input->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history list
 * @input: the history list to be renumbered
 *
 * Return: Always 0 (success)
 */
int renumber_history(Input *input)
{
	list_t *node = input->history;
	int i = 0;

	while (node)
	{
		node->len = i++;
		node = node->next;
	}

	input->histcount = i;
	return (input->histcount);
}
/**
 * get_history_file - gets the history file
 * @input: input struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(Input *input __attribute__((unused)))
{
	char *buf, *dir;

	dir = getenv("HOME");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (strlen(dir) + strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, HISTORY_FILE);

	return (buf);
}

/**
 * store_history - creates a file, or appends to an existing file
 * @input: input struct
 *
 * Return: 1 on success, else -1
 */
int store_history(Input *input)
{
	ssize_t fd;
	char *filename = get_history_file(input);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return (-1);

	for (node = input->history; node; node = node->next)
	{
		write(fd, node->str, strlen(node->str));
		write(fd, "\n", 1);
	}

	write(fd, "\n", 1);
	close(fd);
	return (1);
}
