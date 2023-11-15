#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

extern char **environ;

typedef struct list_s {
    char *str;
    int len;
    struct list_s *next;
} list_t;

// Function prototypes
void _eputs(const char *str);
void _eputchar(char c);
void histlist(char *history_file);
void shell(int readfd, char **av);
void add_env(list_t **head, char *str, int len);
int environ_list(list_t **env);
void clear_info(int *info);
void set_info(int *info, char **av);
int is_interactive(int *info);
ssize_t get_input(int *info);
int identify_builtin(int *info);
void identify_command(int *info);
void store_history(int *info);
void free_info(int *info, int flag);

#define MAX_HISTORY_FILE_LENGTH 256
#define BUF_FLUSH '\n'

#endif /* SHELL_H */
