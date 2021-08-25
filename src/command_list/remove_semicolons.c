#include "../shell.c"

/**
 * name - description
 * @var:
 * @var:
 * Return: int
 */
void remove_semicolons(command_t *node)
{
    int i;
    int *args[100];

    for (i = 0; i < 100; i++)
        if (node->args[i][0] != ';')
            args[i] = node->args[i];

    args[i] = NULL;
    node->args = args;
}