#include "shell.h"
int build_hist_list(char *buffer, int linecount, history)
{
	list_t *node = NULL;

	if (*history)
		node = *history
	appendnode_end(&node, buffer, linecount);
	if (!*history)
		*history = node
	return (0);
}
int renumber_history(list_t **history)
{
	list_t *node = history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	histcount = i;
	return (histcount);
}
/**
 * get_history_file - gets the history file
 * @input: input struct
 *
 * Return: allocated string containing history file
 */
char *get_history_file(Input *input)
{
	char *buf, *dir;

	dir = getenv(input, "HOME=");
	if (!dir)
		return (NULL);

	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);

	buf[0] = 0;
	strcpy(buf, dir);
	strcat(buf, "/");
	strcat(buf, HIST_FILE);

	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
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
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}
