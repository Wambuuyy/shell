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

#define INTERACTIVE_FLAG 1
#define NON_INTERACTIVE_FLAG 0
#define HISTORY_BUFFER_LENGTH 256
#define HIST_MAX 100
#define CMD_NORM 0
#define BUF_FLUSH '\n'
#define MAX_ARGV_SIZE 1024
#define MAX_PATH_SIZE 1024
#define MAX_ENV_SIZE 1024

/**
 * struct Input - Represents the input and state of the shell.
 * @buffer: The main buffer storing the input command.
 * @length: The length of the input buffer.
 * @command_buffer: An array of strings representing
 * a processed command.
 * @linecount_flag: A flag indicating whether line counting is active.
 * @histcount: The history count for tracking command history.
 * @i: The index used for buffer processing.
 * @argv: An array of strings representing command arguments.
 * @ENVIRONMENT: An array of strings representing
 * the environment variables.
 * @path: The path associated with the command.
 * @argc: The number of arguments in the command.
 * @readfd: File descriptor for reading.
 * @history: Linked list for storing command history.
 * @env: Linked list for storing environment variables.
 * @alias: Linked list for storing command aliases.
 * @environ_changed: A flag indicating whether
 * the environment has changed.
 * @status: The status of the last executed command.
 *
 * Description: This structure defines the input
 * and state of the shell,
 * including the main input buffer,
 * processed command buffer, various flags,
 * and linked lists for history,
 * environment variables, and aliases.
 */
typedef struct Input
{
	char *buffer;
	size_t length;
	char **command_buffer;
	int linecount_flag;
	int histcount;
	size_t i;

	char *argv[MAX_ARGV_SIZE];
	char *ENVIRONMENT[MAX_ENV_SIZE];
	char *path;
	int argc;
	int readfd;
	list_t *history;
	list_t *env;
	list_t *alias;
	int environ_changed;
	int status;
} Input;
/**
 * struct list - Represents a node in a linked list.
 * @str: The string content of the node.
 * @len: The length of the string.
 * @next: Pointer to the next node in the list.
 *
 * Description: This structure defines a node in a linked list
 * Each node contains a string (@str), its length (@len),
 * and a pointer to the next node
 * in the list (@next).
 */

typedef struct list
{
	char *str;
	int len;
	struct list *next;
} list_t;


extern char **environ;

/*Function prototypes*/
int unset_alias(char ***alias, char *str);
int set_alias(char ***alias, char *str);
int print_alias(list_t *node);
int check_interactive(int readfd);
int in_delim_set(char c, const char *delimiter);
void handle_comments(char *buf);
int cd_handler(const char *target_path);
int exit_handler(const char *exit_arg);
int history_handler(char **history);
void sigintHandler(int sig_num);
int alias_handler(char ***alias, char **argv, int argc);
void env_handler(char **env);
int populate_env(list_t **env);
int _unsetenv(list_t **env, char *var);
int _setenv(list_t **env, char *var, char *value);
char **get_environ(list_t *env, int *env_changed);
int setfiledes(int fd, int ac, char **av, int *readfd);
ssize_t read_from_fd(int fd, char *buf, size_t *read_count);
ssize_t my_getline(info_t *info, char **linePtr, size_t *lineLength);
void sigintHandler(__attribute__((unused)) int signalNumber);
ssize_t read_buf(info_t *info, char *buffer, size_t *iterator);
void clear_info(char *arg, char **argv, char *path, int *argc);
void print_list(char **list);
void set_info(char *fname, char *arg, char ***argv, int *argc);
void release_info(char ***argv, char **path, char ***environ, int all);
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
void free_string_array(char **array);
void identify_command(char *command, char *const argv[]);
int identify_builtin(char *command, char **argv);
char *identify_path(char *pathstr, char *cmd);
int shell(int *info, char **av);


#endif /* SHELL_H */
