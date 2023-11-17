#include "shell.h"
void handle_error(const char *message)
{
	perror(message);
}
