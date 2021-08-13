#include "../shell.h"

/**
 * _getenv - gets env_var from path
 * @env_var: enviorn variable
 * Return: ret
 */
char *_getenv(char *env_var)
{
	int len, i;

	for (i = 0; environ[i]; i++)
	{

		len = _strstr(environ[i], "=") - environ[i];
		if (_strncmp(environ[i], env_var, len) == 0)
			return (_strstr(environ[i], "=") + 1);
	}
	return (NULL);
}

/**
 * _setenv - custom setenv
 * @env_var: environment variable to set
 * @value: value to set it to
 * Return: the set environment variable
 */
char *_setenv(char *env_var, char *value)
{
	char *ret;

	ret = _getenv(env_var);

	return ((ret) ? _strcpy(ret, value) : NULL);
}
