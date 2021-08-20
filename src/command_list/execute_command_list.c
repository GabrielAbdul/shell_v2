#include "../shell.h"

/**
 * execute_command_list - executes list of commands
 * @commands: linked list of commands
 * Return: status
 */
int execute_command_list(command_t *commands)
{
	command_t *tmp;
	pid_t pid;
	char *path = NULL;
	int stdin_cpy = dup(STDIN_FILENO), stdout_cpy = dup(STDOUT_FILENO), status;

	for (tmp = commands; running && tmp; tmp = tmp->next)
	{
		dup2(tmp->in, STDIN_FILENO);
		dup2(tmp->out, STDOUT_FILENO);
		path = get_path(tmp->command);
		if (_strcmp(tmp->command, "cd") == 0)
			status = cd(tmp);
		else if (_strcmp(tmp->command, "exit") == 0)
			status = myexit(tmp->args);
		else if (_strcmp(tmp->command, "env") == 0)
			status = env(environ);
		else if (!path)
		{
			status = 127;
			_dprintf(STDERR_FILENO, "%s: command not found\n", tmp->command);
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(path, tmp->args, environ) == -1)
				{
					perror("execve");
					return (-1);
				}
			}
			wait(&status);
		}
		free(path), path = NULL;
		close(STDIN_FILENO), close(STDOUT_FILENO);
		close(tmp->in), close(tmp->out);
		dup2(stdin_cpy, STDIN_FILENO), dup2(stdout_cpy, STDOUT_FILENO);
	}
	return (status);
}
