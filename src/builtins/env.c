#include "../shell.h"

/**
 * env - prints the current enviornment
 * @env: enviornment array
 * Return: 0
 */
int env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
		printf("%s\n", env[i]);

	return (0);
}
