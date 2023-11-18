#include "shell.h"
/**
 * handle_error - Prints an error message along with the
 * corresponding system error message.
 * @message: The custom error message to be displayed.
 */
void handle_error(const char *message)
{
	perror(message);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, const char *str)
{
	size_t i = 0;

	while (head)
	{
		if (starts_with(head,str))
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
