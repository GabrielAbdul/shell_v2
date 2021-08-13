#include "../shell.h"

/**
 * myexit - exit builting
 * @args: args to exit ex exit(1)
 * Return: status
 */
int myexit(char **args)
{
	int status, i;

	if (args[1] == NULL)
	{
		running = false;
		return (0);
	}

	for (i = 0; args[1][i]; i++)
		if (i < 48 || i > 57)
			dprintf(STDERR_FILENO, "hsh: %d: Illegal number: %s", line_no, args[1]);
	running = false;
	status = atoi(args[1]);
	return (status);
}
