#include "shell.h"

/**
 * _getline - Custom implementation of getline function
 * @input: Input structure containing information about the shell
 * @ptr: Pointer to the buffer to store the input
 * @length: Pointer to the length of the buffer
 *
 * Return: Number of characters read on success, -1 on failure
 */
int _getline(Input *input, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = *ptr, *new_p = NULL, *c;
	int newline_pos;


	if (p && length)
		s = *length;

	if (i == len)
		i = len = 0;

	r = read_buf(input, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	newline_pos = find_newline(buf, i, len);
	k = newline_pos != -1 ? (size_t)(newline_pos - i + 1) : len;
	new_p = realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? (free(p), (-1)) : (-1));

	add_buf(new_p, buf + i, k - i, s);

	s += k - i;
	i = newline_pos != -1 ? (size_t)newline_pos + 1 : k;

	if (length)
		*length = s;

	*ptr = new_p;
	return (s);
}
/**
 * realloc_str - Reallocates memory for a string
 * @old: Pointer to the old string
 * @old_len: Length of the old string
 * @new_len: Length of the new string
 *
 * Return: Pointer to the reallocated string
 */
char *realloc_str(char *old, size_t old_len, size_t new_len)
{
	return (realloc(old, new_len));
}

/**
 * add_buf - Appends source string to destination buffer
 * @dst: Destination buffer
 * @src: Source string to be appended
 * @d_size: Size of the destination buffer
 * @s_len: Length of the source string
 *
 * Return: 0 on success, -1 on failure
 */
ssize_t add_buf(char *dst, const char *src, size_t d_size, size_t s_len)
{
	if (src_len >= dst_size)
		return (-1);

	strncat(dst, src, src_len);
	return (0);
}

/**
 * find_newline - Finds the position of the newline character in a buffer
 * @buf: Buffer to search for newline character
 * @start: Starting position for the search
 * @len: Length of the buffer
 *
 * Return: Position of the newline character if found, -1 otherwise
 */
int find_newline(const char *buf, size_t start, size_t len)
{
	for (size_t i = start; i < len; i++)
	{
		if (buf[i] == '\n')
			return ((int)i);
	}
	return (-1);
}
