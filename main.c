#include "shell.h"

/**
 * main - Entry point for the shell program.
 * @ac: Number of command-line arguments.
 * @av: Array of strings containing command-line arguments.
 *
 * This function serves as the entry point for the shell program, initializing
 * necessary structures and starting the main shell loop.
 *
 * Return: Integer representing the exit status.
 */
int main(int ac, char **av)
{
	int filedes = 2;
	int readfd = -1;
	Input input;
	char hist_file[256];

	filedes = setfiledes(filedes, ac, av, &readfd);
	populate_env(&input);
	read_hist(hist_file, &input);
	shell(&input, av);

	return (0);
}

/**
 * setfiledes - Sets file descriptors and prepares for command execution.
 * @filedes: File descriptor for redirection.
 * @ac: Number of command-line arguments.
 * @av: Array of strings containing command-line arguments.
 * @readfd: Pointer to the file descriptor for reading.
 *
 * This function sets file descriptors and prepares for command execution,
 * including handling redirection.
 *
 * Return: Integer representing the success or failure
 * of file descriptor setup.
 */
int setfiledes(int filedes, int ac, char **av, int *readfd)
{
	int opened_fd;

	filedes += 3;
	if (ac == 2)
	{
		opened_fd = open(av[1], O_RDONLY);
		if (opened_fd == -1)
		{
			if (errno == EACCES)
			{
				perror("Error during file opening");
				exit(126);
			}
			if (errno == ENOENT)
			{
				fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
				exit(127);
			}
			perror("Error during file opening");
			return (-1);
		}
		*readfd = opened_fd;
		return (opened_fd);
	}
	return (filedes);
}

/**
 * populate_env - Populates the environment variables in the Input structure.
 * @input: Pointer to the Input structure.
 *
 * This function populates the environment variables in the Input structure
 * based on the current environment.
 *
 * Return: Void.
 */
int populate_env(Input *input)
{
	list_t *node = NULL;
	size_t itr;

	while (environ[itr])
	{
		appendnode_end(&node, environ[itr], 0);
		itr++;
	}
	input->env = node;
	return (0);
}

/**
 * read_hist - Reads the command history from a specified file.
 * @history_file: Path to the history file.
 * @input: Pointer to the Input structure.
 *
 * This function reads the command history from the
 * specified file and populates
 * the history list in the Input structure accordingly.
 *
 * Return: Void.
 */
void read_hist(char *history_file, Input *input)
{
	int linecount = 0;
	int filedes = open(history_file, O_RDONLY);
	struct stat st;
	char *buffer;
	ssize_t readlen;
	int last = 0;

	if (filedes == -1 || fstat(filedes, &st) == -1 || st.st_size < 2)
	{
		handle_error("Error: Unable to open history file for reading");
		close(filedes);
		return;
	}
	buffer = malloc(st.st_size + 1);
	if (!buffer)
	{
		handle_error("Memory allocation error");
		close(filedes);
		return;
	}
	readlen = read(filedes, buffer, st.st_size);
	if (readlen <= 0)
	{
		handle_error("Error reading from history file");
		free(buffer);
		close(filedes);
		return;
	}
	close(filedes);
	buffer[st.st_size] = '\0';
	hist_buf(input, st.st_size, &buffer, &last);
	free(buffer);
	while (linecount-- >= HISTORY_MAX)
		delete_index_node(&(input->history), 0);
	renumber_history(input);
}

/**
 * shell - Main function for the shell.
 * @input: Pointer to the Input structure.
 * @av: Array of strings containing command-line arguments.
 *
 * This function serves as the main loop for the shell, processing user input
 * and executing commands until the exit condition is met.
 *
 * Return: Integer representing the exit status.
 */
int shell(Input *input, char **av)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_info(input);
		print_prompt(input);

		input_result = get_input(input);
		process_input(input, av, input_result, &builtin_result);
	}
	store_history(input);
	release_info(input, 1);
	if (!check_interactive(input) && av[1])
	{
		exit(input->status);
	}

	if (builtin_result == -2)
	{
		if (input->status == -1)
		{
			exit(input->status);
		}
		exit(input->status);
	}
	return (builtin_result);
}
