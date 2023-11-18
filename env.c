#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @input: Input struct
 * Return: String array copy of the environment
 */
char **get_environ(Input *input)
{
	if (!input->environment || input->new_env)
	{
		char **new_environment;
		size_t count = count_nodes(input->env);
		size_t i = 0;
		list_t *current;


		/* Allocate memory for the array of strings */
		new_environment = malloc((count + 1) * sizeof(char *));
		if (!new_environment)
		{
			/* Handle memory allocation failure */
			perror("Error allocating memory");
			exit(EXIT_FAILURE);
		}

	
		/* Copy each string from the list to the array */
		current = input->env;
		while (current != NULL)
		{
			new_environment[i] = strdup(current->str);
			if (!new_environment[i])
			{
				/* Handle strdup failure */
				perror("Error copying string");
				exit(EXIT_FAILURE);
			}
			current = current->next;
			i++;
		}
		/* Null-terminate the array */
		new_environment[i] = NULL;
		/* Free the existing environment before updating */
		free_string_array(input->environment);
		/* Update the input structure */
		for (i = 0; new_environment[i] != NULL; i++)
		{
			input->environment[i] = new_environment[i];
		}

		input->environment[i] = NULL;
		input->new_env = 0;
	}
	return input->environment;
}

/**
 * _unsetenv - Remove an environment variable
 * @input: Input struct
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(Input *input, char *var)
{
	list_t *node = input->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node, var);
		if (p && *p == '=')
		{
			input->new_env = delete_index_node(&(input->env), i);
			i = 0;
			node = input->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (input->new_env);
}

/**
 * _setenv - Initialize a new environment variable,
 * or modify an existing one
 * @input: Input struct
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _setenv(Input *input, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return (1);


	strcpy(buf, var);
	strcat(buf, "=");
	strcat(buf, value);

	node = input->env;
	while (node)
	{
		p = starts_with(node, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			input->new_env = 1;
			return (0);
		}
		node = node->next;
	}


	appendnode_end(&(input->env), buf, 0);
	free(buf);
	input->new_env = 1;

	return (0);
}
/**
 * count_nodes - Counts the number of nodes in a linked list.
 * @head: Pointer to the head of the linked list.
 *
 * This function traverses a linked list and counts the number of nodes it contains.
 *
 * Return: The number of nodes in the linked list.
 */
size_t count_nodes(list_t *head)
{
	size_t count = 0;
        list_t *current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}

	return (count);
}
