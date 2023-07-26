#ifndef _SHELL1_H_
#define _SHELL1_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

/* for convert_number() */
#define CONVERT_LOWERCASE   1
#define CONVERT_UNSIGNED    2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE   ".simple_shell_history"
#define HIST_MAX    4096

extern char **custom_environ;

/**
 * struct StringNode - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct StringNode
{
    int num;
    char *str;
    struct StringNode *next;
} StringList;

/**
 *struct CommandInfo - contains pseudo-arguements to pass into a function,
 *              allowing a uniform prototype for a function pointer struct
 *@arguments: a string generated from getline containing arguments
 *@arg_values: an array of strings generated from arguments
 *@command_path: a string path for the current command
 *@arg_count: the argument count
 *@line_counter: the error count
 *@error_num: the error code for exit()s
 *@linecount_flag: if on, count this line of input
 *@filename: the program filename
 *@env_list: linked list local copy of the environment
 *@history: the history node
 *@alias_list: the alias node
 *@env_changed: on if environment was changed
 *@exit_status: the return status of the last exec'd command
 *@command_buffer: address of the pointer to the command buffer, on if chaining
 *@command_buffer_type: CMD_type ||, &&, ;
 *@read_file_descriptor: the file descriptor from which to read line input
 *@histcount: the history line number count
 */
typedef struct CommandInfo
{
    char *arguments;
    char **arg_values;
    char *command_path;
    int arg_count;
    unsigned int line_counter;
    int error_num;
    int linecount_flag;
    char *filename;
    StringList *env_list;
    StringList *history;
    StringList *alias_list;
    char **custom_environ;
    int env_changed;
    int exit_status;

    char **command_buffer; /* pointer to command chaining buffer, for memory management */
    int command_buffer_type; /* CMD_type ||, &&, ; */
    int read_file_descriptor;
    int histcount;
} ShellInfo;

#define SHELL_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

/**
 *struct BuiltinCommand - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct BuiltinCommand
{
    char *type;
    int (*func)(ShellInfo *);
} BuiltinTable;


/* shell_loop.c */
int shell_loop(ShellInfo *, char **);
int find_builtin(ShellInfo *);
void find_command(ShellInfo *);
void fork_command(ShellInfo *);

/* shell_parser.c */
int is_command(ShellInfo *, char *);
char *duplicate_characters(char *, int, int);
char *find_command_path(ShellInfo *, char *, char *);

/* loop_shell.c */
int loop_shell(char **);

/* shell_errors.c */
void custom_puts(char *);
int custom_putchar(char);
int put_to_fd(char c, int fd);
int puts_to_fd(char *str, int fd);

/* shell_string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* shell_string1.c */
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void custom_puts(char *);
int custom_putchar(char);

/* shell_exits.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* shell_tokenizer.c */
char **string_to_words(char *, char *);
char **string_to_words2(char *, char);

/* shell_realloc.c */
char *custom_memset(char *, char, unsigned int);
void custom_free(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* shell_memory.c */
int block_free(void **);

/* shell_atoi.c */
int interactive_shell(ShellInfo *);
int is_delimiter(char, char *);
int custom_isalpha(int);
int custom_atoi(char *);

/* shell_errors1.c */
int custom_error_atoi(char *);
void print_custom_error(ShellInfo *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* shell_builtin.c */
int my_custom_exit(ShellInfo *);
int my_custom_cd(ShellInfo *);
int my_custom_help(ShellInfo *);

/* shell_builtin1.c */
int my_custom_history(ShellInfo *);
int my_custom_alias(ShellInfo *);

/* getline_shell.c */
ssize_t get_input(ShellInfo *);
int custom_getline(ShellInfo *, char **, size_t *);
void sigint_handler(int);

/* shell_getinfo.c */
void clear_shell_info(ShellInfo *);
void set_shell_info(ShellInfo *, char **);
void free_shell_info(ShellInfo *, int);

/* shell_environ.c */
char *get_custom_environment(ShellInfo *, const char *);
int my_custom_env(ShellInfo *);
int my_custom_setenv(ShellInfo *);
int my_custom_unsetenv(ShellInfo *);
int populate_env_list(ShellInfo *);

/* shell_getenv.c */
char **get_custom_environ(ShellInfo *);
int custom_unsetenv(ShellInfo *, char *);
int custom_setenv(ShellInfo *, char *, char *);

/* shell_history.c */
char *get_history_file(ShellInfo *info);
int write_history(ShellInfo *info);
int read_history(ShellInfo *info);
int build_history_list(ShellInfo *info, char *buf, int linecount);
int renumber_history(ShellInfo *info);

/* shell_lists.c */
StringList *add_node(StringList **, const char *, int);
StringList *add_node_end(StringList **, const char *, int);
size_t print_string_list(const StringList *);
int delete_node_at_index(StringList **, unsigned int);
void free_string_list(StringList **);

/* shell_lists1.c */
size_t list_length(const StringList *);
char **list_to_strings(StringList *);
size_t print_list(const StringList *);
StringList *node_starts_with(StringList *, char *, char);
ssize_t get_node_index(StringList *, StringList *);

/* shell_vars.c */
int is_chaining(ShellInfo *, char *, size_t *);
void check_chaining(ShellInfo *, char *, size_t *, size_t, size_t);
int replace_alias(ShellInfo *);
int replace_vars(ShellInfo *);
int replace_string(char **, char *);

#endif
