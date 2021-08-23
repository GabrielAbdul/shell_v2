#include "../shell.h"

/**
 * sigint_handler - handles sigint
 * @status: unused
 */
void sigint_handler(int status)
{
	(void)status;
	write(1, "\n$ ", 3);
}
