# include "shell.h"

int main(int ac, char **av)
{
	int filedes = 2;
	int readfd = -1;
	list_t *environment_list = NULL;
	list_t *hist_list = NULL;
	char hist_file[HISTORY_BUFFER_LENGTH];

	filedes = setfiledes(filedes, ac, av, &readfd);
	populate_env(&environment_list);
	read_hist(hist_file, &hist_list);
	shell(readfd, av, hist_list);

	return (0);
}

int setfiledes(int filedes, int ac, char **av, int *readfd)
{
	int opened_fd;
	filedes +=3;

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
		readfd = opened_fd;
		return (opened_fd);
	}
	return (filedes);
}

int populate_env(list_t **env_list)
{
	list_t *node = NULL;
	size_t itr;

	while (environ[itr])
	{
		appendnode_end(&node, environ[itr], 0);
		itr++;
	}
	*env = node;
	return (0);
}

void read_hist(char *history_file, list_t **history)
{
	int linecount = 0;
	int filedes;
	struct stat st;
	char *buffer;
	ssize_t readlen;
	int last = 0, i = 0;

	filedes = open(history_file,O_RDONLY);
	if (filedes == -1)
	{
		handle_error("Error: Unable to open history file for reading");
		return;
	}

	if (fstat(filedes, &st) == -1)
	{
		handle_error("Error getting file information");
		close(filedes);
		return;
	}
	if (st.st_size < 2)
	{
		close(filedes);
		return;
	}

	buffer = malloc(st.st_size + 1);
	if (!buffer)
	{
		handle_error("Memory allocation error");
		close(fd);
		return;
	}

	readlen = read(filedes, buffer, st.st_size);
	buffer[st.st_size] = '\0';

	if (readlen <= 0)
	{
		handle_error("Error reading from history file");
		free(buffer);
		close(filedes);
		return;
	}

	close(fd);

	while (i < st.st_size)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			build_history_list(buffer + last, linecount++);
			last = i + 1;
		}
		i++;
	}

	if (last != st.st_size)
		build_history_list(buffer + last, linecount++, history);

	free(buffer);

	while (linecount-- >= HIST_MAX)
		delete_index_node(history, 0);

	renumber_history(*history);
}

int shell(Input *input, char **av)
{
	ssize_t input_result = 0;
	int builtin_result = 0;

	while (input_result != -1 && builtin_result != -2)
	{
		clear_info(info);
		print_prompt(info);

		input_result = readcess_input(info);
		process_input(info, av, input_result, &builtin_result);
	}
	store_history(info, hist_list);
	release_info(info, 1);
	if (!is_interactive(info) && info[1])
	{
		exit(info[1]);
	}

	if (builtin_result == -2)
	{
		if (info[2] == -1)
		{
			exit(info[1]);
		}
		exit(info[2]);
	}
	return (builtin_result);
}
