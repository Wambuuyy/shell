#include "shell.h"

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(Input *input)
{
	int i;
	char *p;
	char *alias_value;

	for (i = 0; i < 10; i++)
	{
		alias_value = starts_with(input->alias, input->argv[0]);
		if (!alias_value)
			return (0);
		free(input->argv[0]);
		p = strchr(alias_value, '=');
		if (!p)
			return (0);
		p = strdup(p + 1);
		if (!p)
			return (0);
		input->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(Input *input)
{
	int i = 0;
	char *alias_value;

	for (i = 0; input->argv[i]; i++)
	{
		if (input->argv[i][0] != '$' || !input->argv[i][1])
			continue;

		if (strcmp(input->argv[i], "$?") == 0)
		{
			replace_string(&(input->argv[i]), strdup(convert_number(input->status, 10, 0)));
			continue;
		}
		if (strcmp(input->argv[i], "$$") == 0)
		{
			replace_string(&(input->argv[i]), strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		alias_value = starts_with(input->alias, input->argv[0]);
		if (alias_value)
		{
			  replace_string(&(input->argv[i]), strdup(strchr(alias_value, '=') + 1));
			  continue;
		}
		else
		{
			replace_string(&input->argv[i], strdup(""));
			fprintf(stderr, "Error: Alias not found\n");
		}
	}
	return (0);
}
/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);


	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
