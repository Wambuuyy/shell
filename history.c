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
