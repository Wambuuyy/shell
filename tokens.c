#include "shell.h"

/**
 * strtok_str - Splits a string into words based on delimiters
 * @input_string: Input string to be split
 * @delimiters: String containing delimiter characters
 *
 * Return: Array of strings (words) or NULL on failure
 */
char **strtok_str(char *input_string, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **words;

	if (input_string == NULL || input_string[0] == '\0')
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (i = 0; input_string[i] != '\0'; i++)
	{
		if (!is_delimiter(input_string[i], delimiters) &&
				(is_delimiter(input_string[i + 1], delimiters) || !input_string[i + 1]))
		{
			num_words++;
		}
	}
	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(input_string[i], delimiters))
			i++;
		k = 0;
		while (!is_delimiter(input_string[i + k], delimiters) && input_string[i + k])

			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			free_string_array(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = input_string[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;
	return (words);
}

/**
 * strtok_single - Splits a string into words based on a single delimiter
 * @input_string: Input string to be split
 * @delimiter: Single delimiter character
 *
 * Return: Array of strings (words) or NULL on failure
 */
char **strtok_single(char *input_string, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **words;

	if (input_string == NULL || input_string[0] == '\0')
		return (NULL);

	for (i = 0; input_string[i] != '\0'; i++)
		if ((input_string[i] != delimiter &&
					input_string[i + 1] == delimiter) || (input_string[i] != delimiter &&
						!input_string[i + 1]) || input_string[i + 1] == delimiter)
			num_words++;

	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (!words)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input_string[i] == delimiter && input_string[i] != delimiter)
			i++;
		k = 0;
		while (input_string[i + k] != delimiter &&
				input_string[i + k] && input_string[i + k] != delimiter)
			k++;
		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			free_string_array(words);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			words[j][m] = input_string[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;
	return (words);
}

/**
 * is_delimiter - Checks if a character is a delimiter
 * @character: Character to check
 * @delimiters: String containing delimiter characters
 *
 * Return: 1 if character is a delimiter, 0 otherwise
 */
int is_delimiter(char character, char *delimiters)
{
	while (*delimiters)
		if (*delimiters++ == character)
			return (1);
	return (0);
}

/**
 * free_string_array - Frees memory allocated for a string array
 * @array: Array of strings to be freed
 *
 * Return: void
 */
void free_string_array(char **array)
{
	size_t i;

	if(!array)
	{
		return;
	}
	
	for (i = 0; array[i] != NULL; i++)
		free(array[i]);
	free(array);
}
