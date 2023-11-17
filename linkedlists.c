#include "shell.h"

void appendnode_end(list_t **head, char *str, int len)
{
	list_t *new_node, *current;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	new_node->str = strdup(str);
	if (new_node->str == NULL)
	{
		fprintf(stderr, "String duplication error\n");
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->len = len;
	new_node->next = NULL;

	current = *head;
	
	if (current == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}
int delete_index_node(list_t **head, unsigned int index)
{
	list_t *node;
	list_t *prev_node = NULL;
	unsigned int i = 0;

	if (!head || !*head)
	{
		return (0);
	}
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return 1;
	}
	while (node && i != index)
	{
		prev_node = node;
		node = node->next;
		i++;
	}
	if (node)
	{
		prev_node->next = node->next;
		free(node->str);
		free(node);
		return(1);
	}
	return (0);
}
