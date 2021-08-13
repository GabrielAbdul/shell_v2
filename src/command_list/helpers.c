#include "../shell.h"

/**
 * _strstr - custom strstr
 * @haystack: string to search
 * @needle: string to find in haystack
 * Return: pointer to position of needle in haystack
 */
char *_strstr(char *haystack, char *needle)
{
	size_t i;
	size_t needle_len = _strlen(needle);

	if (!haystack || !needle)
		return (NULL);

	for (i = 0; haystack[i]; i++)
		if (_strncmp(haystack + i, needle, needle_len) == 0)
			return (haystack + i);

	return (NULL);
}
/**
 * _strncmp - custom strncmp
 *
 * @a: string a
 * @b: string b
 * @n: number of bytes to compare
 * Return: 0 if same, else, difference
 */
int _strncmp(char *a, char *b, size_t n)
{

	while (n && *a && *b)
	{
		if (*a != *b)
			break;
		--n, ++a, ++b;
	}

	if (n == 0)
		return (0);

	return (*a - *b);
}
/**
 * _strcmp - custom _strcmp
 *
 * @a: string a
 * @b: string b
 * Return: difference between first unequal byte, or 0 if they are equal
 */
int _strcmp(char *a, char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			break;
		++a, ++b;
	}
	return (*a - *b);
}
/**
 * _dprintf - custom dprintf
 * @fd: file descriptor
 * @s: string
 * Return: number of characters printed
 */
int _dprintf(int fd, char *s, ...)
{
	char buffer[1024];
	int i = 0, j = 0;
	va_list list;
	char *tmp_str;

	va_start(list, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			buffer[j++] = s[i++];
			continue;
		}
		if (s[i + 1] == 's')
		{
			tmp_str = va_arg(list, char *);
			if (!tmp_str)
				j += sprintf(buffer + j, "%s", "(null)");
			else
				j += sprintf(buffer + j, "%s", tmp_str);
		}
		else if (s[i + 1] == 'd')
		{
			j += sprintf(buffer + j, "%d", va_arg(list, int));
		}
		else /* unknown format specifier, so print "%<spec>" */
		{
			buffer[j++] = s[i++];
			buffer[j++] = s[i++];
		}
		i += 2;
	}
	buffer[j] = '\0';
	va_end(list);
	return (write(fd, buffer, j));
}
