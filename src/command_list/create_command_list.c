#include "../shell.h"

#define APPEND_PERMS (O_APPEND | O_CREAT | O_RDWR)
#define REDIR_PERMS (O_RDWR | O_CREAT | O_TRUNC)

/**
 * IO - assignes input and output for pipes
 * @command: command node
 */
void IO(command_t *command)
{
	int pipefds[2];
	static int in = STDIN_FILENO, out = STDOUT_FILENO;

	if (command->type == PIPE)
	{
		command->in = in;
		pipe(pipefds);
		command->out = pipefds[WRITE_END];
		in = pipefds[READ_END];
		out = STDOUT_FILENO;
		return;
	}
	if (IS_REDIR(command->type))
	{
		if (command->type == REDIR_LEFT)
		{
			command->in = open(command->in_file, O_RDONLY);
			command->out = out;
		}
		else if (command->type == REDIR_RIGHT)
		{
			command->in = in;
			command->out = open(command->out_file, REDIR_PERMS, 0644);
		}
		else if (command->type == APPEND)
		{
			command->in = in;
			command->out = open(command->out_file, APPEND_PERMS, 0644);
		}
		command->args[command->num_args - 1] = NULL;
		command->args[command->num_args - 2] = NULL;
		command->num_args -= 2;
	}
	else
		command->in = in, command->out = out;
	in = STDIN_FILENO, out = STDOUT_FILENO;
}

/**
 * set_args - Set the args parameter for command node
 * @node: command node
 */
void set_args(command_t *node)
{
	int i, is_redirect_file = false;
	char *tokens;

	for (i = 1; (tokens = strtok(NULL, " ")) != NULL; i++)
	{
		if (_strcmp(tokens, ";") == 0)
		{
			i--;
			continue;
		}
		node->args[i] = tokens;
		if (is_redirect_file)
		{
			if (node->type == APPEND || node->type == REDIR_RIGHT)
				node->out_file = tokens;
			else if (node->type == REDIR_LEFT)
				node->in_file = tokens;
			is_redirect_file = false;
		}

		if (_strcmp(tokens, ">") == 0)
			node->type = REDIR_RIGHT;
		else if (_strcmp(tokens, ">>") == 0)
			node->type = APPEND;
		else if (_strcmp(tokens, "<") == 0)
			node->type = REDIR_LEFT;
		else if (_strcmp(tokens, "<<") == 0)
			node->type = HEREDOC;

		is_redirect_file = (node->type != SEMIC);
	}
	node->args[i] = NULL;
	node->num_args = i;
}

/**
 * create_command_node - creates a new command n ode
 * @prev: previous node
 * @command: command node
 * Return: new node
 */
command_t *create_command_node(char *command, command_t *prev)
{
	command_t *node;
	char *separators[] = {"&&", "&", "||", "|"};
	int separator_types[] = {AND, ASYNC, OR, PIPE};
	size_t j;

	node = malloc(sizeof(command_t));
	node->next = NULL;
	node->prev = prev;
	node->type = SEMIC;
	node->in = STDIN_FILENO;
	node->out = STDOUT_FILENO;
	node->command = strtok(command, " ");
	node->args[0] = command;
	/* add each command into our commands array */
	set_args(node);

	for (j = 0; j < ARRAY_SIZE(separators); j++)
	{
		if (_strcmp(node->args[node->num_args - 1], separators[j]) == 0)
		{
			node->type = separator_types[j];
			node->args[node->num_args - 1] = NULL;
			node->num_args -= 1;
			break;
		}
	}
	IO(node);
	return (node);
}

/**
 * create_command_list - creates list of commands
 * @commands_string: commands string
 * Return: list of commands
 */
command_t *create_command_list(char *commands_string)
{
	int i, con, j;
	char **commands;
	command_t *command_node = NULL, *tmp, *head = NULL;

	/* split commands_string into separate commands */
	commands = split_line_into_commands(commands_string);

	/* create node with info */
	for (i = 0; commands[i]; i++)
	{
		for (j = 0; commands[i][j]; j++)
		{
			if (commands[i][j] == '#')
			{
				con = 1;
				break;
			}
		}
		if (con == 1)
			continue;
		if (i == 0)
		{
			head = create_command_node(commands[i], NULL);
			command_node = head;
		}
		else
		{
			tmp = command_node;
			command_node = create_command_node(commands[i], command_node);
			tmp->next = command_node;
		}
	}

	free(commands);
	return (head);
}

/**
 * split_line_into_commands - splits line into commands
 * @line: line
 * Return: split line
 */
char **split_line_into_commands(char *line)
{
	char *last_command, *pos = NULL, *seps[] = {"&&", "||", "|", "&", ";"};
	char **commands = malloc(sizeof(char *) * MAX_ARG_SIZE);
	int i, sep_len;
	size_t j;

	for (i = 0; *line && (pos || !i); i++)
	{
		commands[i] = line;
		last_command = line;
		for (j = 0; j < ARRAY_SIZE(seps); j++)
		{
			pos = _strstr(line, seps[j]);
			if (pos)
			{
				sep_len = _strlen(seps[j]);
				pos[sep_len] = '\0';
				line = pos + sep_len + 1;
				break;
			}
		}
	}
	commands[i] = NULL;
	sep_len = _strlen(last_command) - 1;
	if (last_command[sep_len] == '\n')
		last_command[sep_len] = '\0';
	return (commands);
}
