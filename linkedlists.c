#include "shell.h"
/**
 * appendnode_end - Appends a new node at the end of a linked list.
 * @head: Pointer to the head of the linked list.
 * @str: The string to be stored in the new node.
 * @len: The length of the string.
 *
 * This function adds a new node with the specified
 * string and length to the
 * end of the linked list.
 * It ensures proper allocation and linkage of nodes.
 *
 * Return: 1 if successful, 0 on failure.
 */

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

/**
 * delete_index_node - Deletes a node at a specified
 * index in a linked list.
 * @head: Pointer to the head of the linked list.
 * @index: The index of the node to be deleted.
 *
 * This function removes the node at the given index in the linked l    ist. It
 * ensures proper cleanup and maintains the integrity of the linked     list.
 *
 * Return: 1 if successful, 0 if the index is out of range or
 * on fai    lure.
 */
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
		return (1);
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
		return (1);
	}
	return (0);
}
/**
 * custom_strtok - Custom implementation of strtok
 *
 * @input_string: The input string to be tokenized
 * @delimiters: A string containing delimiter characters
 *
 * Return: An array of strings (tokens) or NULL on failure
 *
 * This function provides a custom implementation of strtok that can switch
 * between two different implementations: strtok_str and strtok_single.
 * It checks if the delimiters contain '\t' and calls the appropriate
 * implementation accordingly. The resulting array of tokens is dynamically
 * allocated and should be freed by the caller when no longer needed.
 */
char **custom_strtok(char *input_string, char *delimiters)
{
	if (strchr(delimiters, '\t') != NULL)
	{
		/* Call strtok_str for whitespace and tabs*/
		return strtok_str(input_string, delimiters);
	}
	else
	{
		/* Call strtok_single for a single delimiter*/
		return strtok_single(input_string, delimiters[0]);
	}
}	
