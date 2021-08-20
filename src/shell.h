#ifndef SHELL_H
#define SHELL_H

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdarg.h>

extern char **environ;
int line_no;
int running;
char *program_name;

#define READ_SIZE 2048

#define PATH_SIZE 40
#define MAX_ARG_SIZE 50

#define SEMIC 0
#define OR 1
#define AND 2
#define ASYNC 3
#define PIPE 4
#define REDIR_LEFT 5
#define REDIR_RIGHT 6
#define HEREDOC 7
#define APPEND 8

#define READ_END 0
#define WRITE_END 1

#define true 1
#define false 0

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define IS_REDIR(x) (x == REDIR_LEFT || x == REDIR_RIGHT || x == APPEND)

/**
 * struct command_s - struct
 * @type: type
 * @command: command
 * @args: args
 * @in_file: input file name
 * @out_file: output file name
 * @in: file descriptor for input
 * @out: file descriptor for output
 * @num_args: number of argument in command
 * @next: next command node
 * @prev: previous command node
 */
struct command_s
{
	int type;
	char *command;
	char *args[MAX_ARG_SIZE];
	char *in_file;
	char *out_file;
	int in;
	int out;
	int num_args;
	struct command_s *next;
	struct command_s *prev;
};
typedef struct command_s command_t;

/* command list protos */
int execute_command_list(command_t *commands);
char *get_path(char *command);
char *search_path_directories(char **dirs, char *command, int size);
int find_flags_and_execute(command_t *command);
command_t *create_command_list(char *commands_string);
command_t *create_command_node(char *commands, command_t *prev);
void set_args(command_t *node);
char **split_line_into_commands(char *line);

/* builtins */
int cd(command_t *node);
int myexit(char **args);
int env(char **env);

/* strings */
char *_strstr(char *haystack, char *needle);
int _strncmp(char *a, char *b, size_t n);
int _strcmp(char *a, char *b);
int _dprintf(int fd, char *s, ...);
size_t _strlen(char *s);
char *_strncpy(char *dest, char *src, int n);
char *_strcpy(char *dest, char *src);
char *_strdup(char *s);
char *_getenv(char *env_var);
char *_setenv(char *env_var, char *value);
void sigint_handler(int status);

void free_commands(command_t *head);

#endif /* SHELL_H */
