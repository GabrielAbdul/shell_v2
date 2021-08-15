#include "../shell.h"

/**
 * myexit - exit builting
 * @args: args to exit ex exit(1)
 * Return: status
 */
int myexit(char **args)
{
	int status;

	if (args[1] == NULL)
	{
		running = false;
		return (0);
	}

	running = false;
	status = atoi(args[1]);
	return (status);
}
