#include "shell.h"

/**
 * unset_alias - sets alias to string
 * @input: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(Input *input, char *str)
{
	char *p, c;
	int ret;
	
	p = strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_index_node(&(input->alias),
			get_node_index(input->alias, str));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @input: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(Input *input, char *str)
{
	char *p;

	p = strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(input, str));


	unset_alias(input, str);

	appendnode_end(&(input->alias), str, 0);
	return (0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			putchar(*a);
		putchar('\'');
		puts(p + 1);
		puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * create_list_node - Creates a new list node.
 * @str: The string to be stored in the node.
 * @next: Pointer to the next node in the list.
 *
 * Return: A pointer to the newly created node or NULL on failure.
 */
list_t *create_list_node(const char *str, list_t *next)
{
	/* Allocate memory for the new node */
	list_t *newNode = (list_t *)malloc(sizeof(list_t));
	        
	/* Check for memory allocation failure */
	if (newNode == NULL)
	{
		/* Handle memory allocation failure */
		return NULL;
	}

	/* Allocate memory for the string and copy it */
	newNode->str = strdup(str);

	/* Check for memory allocation failure */
	if (newNode->str == NULL)
	{
		/* Handle memory allocation failure */
		free(newNode);
		return NULL;
	}

	/* Set the next pointer */
	newNode->next = next;

	/* Return a pointer to the newly created node */
	return newNode;
}
