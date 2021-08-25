#include "shell.h"
#include <stdio.h>

/**
 * main - entry point for shell_v2
 * @ac: argument count
 * @argv: argument vector
 * Return: status
 */
int main(int ac, char **argv)
{
	int status = 1;
	int bytes;
	char *line = NULL;
	size_t line_size = 0;
	command_t *commands;

	(void)ac;
	
	signal(SIGINT, sigint_handler);
	line_no = 0;
	running = true;
	program_name = argv[0];

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	while (running && (bytes = getline(&line, &line_size, stdin)) > 0)
	{

		line_no++;
		if (bytes == 1)
			continue;
		commands = create_command_list(line);
		status = execute_command_list(commands);
		free_commands(commands);
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
	}
	free(line);
	if (status != 0)
		exit(2);
	return (status);
}
