#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @input: Input struct
 * Return: String array copy of the environment
 */
char **get_environ(Input *input)
{
	if (!input->environ || input->env_changed)
	{

		input->environ = list_to_strings(input->env);
		input->env_changed = 0;
	}

	return (input->environ);
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
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			input->env_changed = delete_node_at_index(&(input->env), i);
			i = 0;
			node = input->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (input->env_changed);
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

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);


	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = input->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			input->env_changed = 1;
			return (0);
		}
		node = node->next;
	}


	add_node_end(&(input->env), buf, 0);
	free(buf);
	input->env_changed = 1;

	return (0);
}
