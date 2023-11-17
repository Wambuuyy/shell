#include "shell.h"
/**
 * handle_error - Prints an error message along with the
 * corresponding system error message.
 * @message: The custom error message to be displayed.
 */
void handle_error(const char *message)
{
	perror(message);
}
