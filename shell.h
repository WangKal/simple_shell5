#ifndef _SHELL_H_
#define _SHELL_H_

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
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for c_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} kalist_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	kalist_t *env;
	kalist_t *history;
	kalist_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} i_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(i_t *);
} b_table;


/* shloop.c */
int hsh(i_t *, char **);
int find_builtin(i_t *);
void find_cmd(i_t *);
void fork_cmd(i_t *);

/* parser.c */
int is_cmd(i_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(i_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _sputfd(char *str, int fd);

/* string.c */
int _lenstr(char *);
int _cmpstr(char *, char *);
char *with_start(const char *, const char *);
char *_catstr(char *, char *);

/* string1.c */
char *_cpystr(char *, char *);
char *_upstrd(const char *);
void _sput(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **towstr(char *, char *);
char **towstr2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int bfree(void **);

/* atoi.c */
int interactive(i_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int _erratoi(char *);
void print_kaerror(i_t *, char *);
int print_d(int, int);
char *c_number(long int, int, int);
void r_comments(char *);

/* builtin.c */
int _kaexit(i_t *);
int _mycd(i_t *);
int usaidizi(i_t *);

/* builtin1.c */
int _myhistory(i_t *);
int _myalias(i_t *);

/*getline.c */
ssize_t get_input(i_t *);
int _getline(i_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void c_info(i_t *);
void set_info(i_t *, char **);
void f_info(i_t *, int);

/* environ.c */
char *_genv(i_t *, const char *);
int _myenv(i_t *);
int _mysetenv(i_t *);
int _myunsetenv(i_t *);
int populate_env_list(i_t *);

/* getenv.c */
char **get_environ(i_t *);
int _unsetenv(i_t *, char *);
int _setenv(i_t *, char *, char *);

/* history.c */
char *get_history_file(i_t *info);
int w_h(i_t *info);
int soma_history(i_t *info);
int build_history_list(i_t *info, char *buf, int linecount);
int r_h(i_t *info);

/* lists.c */
kalist_t *add_node(kalist_t **, const char *, int);
kalist_t *a_n_e(kalist_t **, const char *, int);
size_t print_list_str(const kalist_t *);
int delete_node_at_index(kalist_t **, unsigned int);
void free_list(kalist_t **);

/* lists1.c */
size_t len_list(const kalist_t *);
char **kalist_to_strings(kalist_t *);
size_t print_list(const kalist_t *);
kalist_t *node_with_start(kalist_t *, char *, char);
ssize_t g_n_i(kalist_t *, kalist_t *);

/* vars.c */
int is_c(i_t *, char *, size_t *);
void check_chain(i_t *, char *, size_t *, size_t, size_t);
int a_replace(i_t *);
int replace_vars(i_t *);
int s_rep(char **, char *);

#endif
