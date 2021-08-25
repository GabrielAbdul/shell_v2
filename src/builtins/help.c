#include "../shell.h"

/**
 * name - description
 * @var:
 * @var:
 * Return: int
 */
int help(command_t *node)
{
    int i;
    char *builtins[6] = {"exit", "cd", "env", "setenv", "unsetenv", NULL};
    char *helpStrings[6] = {
                         "exit: exit [n]\n\tExit the shell.",
                         "cd: cd [dir]\n\tChange directory.",
                         "env: env\n\tList enviornment variables.",
                         "setenv: setenv [VAR] [VALUE]\n\tSet new enviornment variable",
                         "unsetenv: unsetenv [VAR] [VALUE]\n\tUnset enviornment variable",
                         NULL
    };

    if (node->num_args == 1)
    {
        printf("help: help [-dms] [pattern ...]\n");
        return (0);
    }

    i = 0;
    while (builtins[i])
    {
        if (_strcmp(node->args[1], builtins[i]) == 0)
            printf("%s\n", helpStrings[i]);
        i++;
    }
    return (0);
}