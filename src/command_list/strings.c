#include "../shell.h"
/**
 * _strlen - custom strlen
 * @s: string
 * Return: string length
 */
size_t _strlen(char *s)
{
	size_t len = 0;

	if (s)
	{
		while (s[len])
			len++;
	}
	return (len);
}
/**
 * _strncpy - copies n bytes from src to dest
 * @dest: dest pointer
 * @src: src pointer
 * @n: number of bytes to copy
 * Return: pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	if (!dest || !src)
		return (NULL);
	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcpy - copies src onto dest
 * @dest: dest pointer
 * @src: src pointer
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	return (_strncpy(dest, src, _strlen(src)));
}
/**
 * _strdup - custom strdup
 * @s: string
 * Return: copy of s
 */
char *_strdup(char *s)
{
	char *copy = malloc(sizeof(char) * (_strlen(s) + 1));

	return (_strcpy(copy, s));
}
