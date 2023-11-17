int _getline(Input *input, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;

	if (p && length)
	{
		s = *length;
	}

	if (i == len)
	{
		i = len = 0;
	}

	r = read_buf(input, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
	{
		return (-1);
	}

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, s, s ? s + k : k + 1);

	if (!new_p)
	{
		return p ? (free(p), (-1)) : (-1);
	}

	if (s)
	{
		strncat(new_p, buf + i, k - i);
	}
	else
	{
		strncpy(new_p, buf + i, k - i + 1);
	}

	s += k - i;
	i = k;
	p = new_p;

	if (length)
	{
		*length = s;
	}

	*ptr = p;
	return (s);
}
