#include "shell.h"

int main(int ac, char **av)
{
    int fd = 2;
    int readfd = -1;
    list_t *env_list = NULL;
    char history_file[MAX_HISTORY_FILE_LENGTH];
    // Add other variables as needed

    fd = setupFileDescriptor(fd, ac, av, &readfd);
    
    // Assign values to other variables as needed

    populate_env_list(&env_list);
    read_history(history_file);
    shell(readfd, av);
    return (EXIT_SUCCESS);
}
