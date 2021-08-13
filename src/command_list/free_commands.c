#include "../shell.h"

/**
 * free_commands - frees linked list of commands
 * @head: head of linked list
 */
void free_commands(command_t *head)
{
	if (!head)
		return;

	free_commands(head->next);
	free(head);
}
