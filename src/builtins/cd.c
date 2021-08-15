#include "../shell.h"

/**
 * cd - changes directory
 * @node: command node
 * Return: status
 */
int cd(command_t *node)
{
	int status;
	char *HOME, *OLDPWD;
	char *cwd = getcwd(NULL, 256);
	char *err = "%s: %d: cd: can't cd to %s\n";
	int print_dir = false;

	if (node->args[1] == NULL)
	{
		HOME = _getenv("HOME");
		if (!HOME)
		{
			free(cwd);
			return (0);
		}
		status = chdir(HOME);
	}
	else if (_strcmp(node->args[1], "-") == 0)
	{
		OLDPWD = _getenv("OLDPWD");
		if (!OLDPWD)
		{
			printf("%s\n", cwd);
			free(cwd);
			return (0);
		}
		status = chdir(OLDPWD);
		printf("%s\n", OLDPWD);
	}
	else
		status = chdir(node->args[1]);

	if (status == -1)
		dprintf(STDERR_FILENO, err, program_name, line_no, node->args[1]);
	else
		_setenv("OLDPWD", cwd);

	if (print_dir == true)
		_dprintf(STDOUT_FILENO, "%s\n", OLDPWD);
	free(cwd);
	return (status);
}
