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
#define MAX_BUILTIN_TYPES 8
#define HISTORY_FILE "filename"
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define HISTORY_MAX 100
#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3
#define BUF_FLUSH '\n'
#define ARGV_BUF 1024
#define PATH_BUF 1024
#define ENV_BUF 1024
#define READ_BUF 1024
#define WRITE_BUF 1024

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
 * @environment: An array of strings representing
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
	char *filename;
	int linecount_flag;
	int histcount;
	size_t i;
	unsigned int linecount;
	char *argv[ARGV_BUF];
	char *environment[ENV_BUF];
	char *path;
	int error;
	int argc;
	int readfd;
	list_t *history;
	list_t *env;
	list_t *alias;
	int buffer_type;
	int new_env;
	int status;
} Input;

/**
 * struct Builtins - Represents a built-in command.
 * @command: The name of the built-in command.
 * @handler: A function pointer to the handler function.
 */
struct Builtins
{
	const char *command;
	int (*handler)(Input *input);
};

extern char **environ;

/*alias.c*/
int unset_alias(Input *input, char *str);
int set_alias(Input *input, char *str);
int print_alias(list_t *node);
list_t *create_list_node(const char *str, list_t *next);

/*calls.c*/
void print_prompt(Input *input);
int check_interactive(Input *input);
void process_input(Input *input, char **av, ssize_t result, int *bresults);
void hist_buf(Input *input, size_t size, char **buffer, int *last);

/*managers.c  */
void clear_info(Input *input);
void release_info(Input *input, int all);
void set_info(Input *input, char *arg);
void print_list( list_t *list);

/*chain.c*/
int is_chain(Input *input, char *buf, size_t *p);
void check_chain(Input *input, char *buf, size_t *p, size_t i, size_t len);
int env_handler(Input *input);
int unsetenv_handler(Input *input);
int setenv_handler(Input *input);

/*env.c*/
char **get_environ(Input *input);
int _unsetenv(Input *input, char *var);
int _setenv(Input *input, char *var, char *value);
size_t count_nodes(list_t *head);

/*errors.c*/
void handle_error(const char *message);
ssize_t get_node_index(list_t *head, const char *str);

/*getline*/
int _getline(Input *input, char **ptr, size_t *length);
char *realloc_str(char *old, size_t old_len, size_t new_len);
ssize_t add_buf(char *dst, const char *src, size_t d_size, size_t s_len);
int find_newline(const char *buf, size_t start, size_t len);

/*handlers*/
int exit_handler(Input *input);
int cd_handler(Input *input);
int help_handler(Input *input);

/*history.c*/
int build_hist_list(Input *input);
int renumber_history(Input *input);
char *get_history_file(Input *input __attribute__((unused)));
int store_history(Input *input);

/*input*/
void initialize_input(Input *input);
void free_input(Input *input);
ssize_t input_buf(Input *input, char **buf, size_t *len);
ssize_t get_input(Input *input);
ssize_t read_buf(Input *input, char *buf, size_t *i);

/*linkedlists.c*/
void appendnode_end(list_t **head, char *str, int len);
int delete_index_node(list_t **head, unsigned int index);
char **custom_strtok(char *input_string, char *delimiters);

/*main.c*/
int main(int ac, char **av);
int setfiledes(int filedes, int ac, char **av, int *readfd);
int populate_env(Input *input);
void read_hist(char *history_file, Input *input);
int shell(Input *input, char **av);

/*morehandlers*/
void sigintHandler(__attribute__((unused))int sig_num);
int history_handler(Input *input);
int alias_handler(Input *input);
void execute_command(Input *input);
void remove_comments(char *buf);

/*path*/
int is_cmd(Input *input, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(Input *input, char *pathstr, char *cmd);

/*searchers*/
int identify_command(Input *input);
int identify_builtin(Input *input);

/*token*/
char **strtok_str(char *input_string, char *delimiters);
char **strtok_single(char *input_string, char delimiter);
int is_delimiter(char character, char *delimiters);
void free_string_array(char **array);

/*others*/
char *_memset(char *s, char b, unsigned int n);
void ffree(list_t *head);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *starts_with(list_t *node, const char *var);

/*print.c*/
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void print_error(Input *input, char *str);
int bfree(void **ptr);

/*strings*/
char **list_to_strings(list_t *head);
list_t *add_node(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
void free_list(list_t **head_ptr);
size_t list_len(const list_t *h);
/*replace.c*/
int replace_alias(Input *input);
int replace_vars(Input *input);
char *convert_number(long int num, int base, int flags);
int replace_string(char **old, char *new);

#endif /* SHELL_H */
