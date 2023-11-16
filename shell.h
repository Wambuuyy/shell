#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

typedef struct list_s {
    char *str;
    int len;
    struct list_s *next;
} list_t;

#define INTERACTIVE_FLAG 1
#define NON_INTERACTIVE_FLAG 0
#define MAX_HISTORY_FILE_LENGTH 256
#define BUF_FLUSH '\n'

extern char **environ;

/*Function prototypes*/
int unset_alias(char ***alias, char *str);
int set_alias(char ***alias, char *str);
int print_alias(list_t *node);

int cd_handler(const char *target_path);
int exit_handler(const char *exit_arg);
int history_handler(char **history);
void sigintHandler(int sig_num);
int alias_handler(char ***alias, char **argv, int argc);
void env_handler(char **env);
void child_command(char *path, char *const argv[]);/*fork_command*/
void add_env(list_t **head, char *str, int len);/*add env var*/
int populate_env(list_t **env);
int _unsetenv(list_t **env, char *var);
int _setenv(list_t **env, char *var, char *value);
char **get_environ(list_t *env, int *env_changed);
int setFileDes(int fd, int ac, char **av, int *readfd);
ssize_t read_from_fd(int fd, char *buf, size_t *read_count);
ssize_t my_getline(info_t *info, char **linePtr, size_t *lineLength);
void sigintHandler(__attribute__((unused)) int signalNumber);
ssize_t read_buf(info_t *info, char *buffer, size_t *iterator);
void clear_info(char *arg, char **argv, char *path, int *argc);
void print_list(char **list);
void set_info(char *fname, char *arg, char ***argv, int *argc);
void release_info(char ***argv, char **path, char ***cmd_buf, int *readfd, char ***environ, int all);
void read_history(char *history_file);
int store_history(void);
void save_to_file(const char *data, int fd);
int past_commands(const char **history);
void print_list(const char **history);
char *get_history_file(void);
int write_history(void);
int read_history(void);
int build_history_list(char *buf, int linecount);
int renumber_history(void);
void set_info(char *fname, char *arg, char ***argv, int *argc);
ssize_t manage_input(char **buf, size_t *len, char ***cmd_buf, int *linecount_flag, int *histcount);
ssize_t user_input(char **argument, int *command_buffer_type, int *linecount_flag, int *history_count);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
char *starts_with(const char *haystack, const char *needle);
void free_list(list_t **head_ptr);
int main(int ac, char **av);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);
char **strtok_str(char *input_string, char *delimiters);
char **strtok_single(char *input_string, char delimiter);
int is_delimiter(char c, char *delimiters);
void free_string_array(char **array);
void identify_command(char *command, char *const argv[]);
int identify_builtin(char *command, char **argv);
char *identify_path(char *pathstr, char *cmd);
int shell(int *info, char **av);


#endif /* SHELL_H */
