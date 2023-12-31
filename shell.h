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

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_pataline 0
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
} l_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_hesabu: the error count
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
	unsigned int line_hesabu;
	int err_num;
	int linecount_flag;
	char *fname;
	l_t *env;
	l_t *history;
	l_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
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
} builtin_table;


/* toem_shloop.c */
int hsh(i_t *, char **);
int f_b(i_t *);
void f_c(i_t *);
void fork_cmd(i_t *);

/* toem_parser.c */
int is_cmd(i_t *, char *);
char *dup_chars(char *, int, int);
char *f_p(i_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _ep(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _lenstr(char *);
int _cmpstr(char *, char *);
char *with_starts(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_cpystr(char *, char *);
char *_upstrd(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_cpystrn(char *, char *, int);
char *_strncat(char *, char *, int);
char *_chrstr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_allocre.c */
char *_setmem(char *, char, unsigned int);
void ffree(char **);
void *_allocre(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_toia.c */
int interactive(i_t *);
int is_delim(char, char *);
int _alphais(int);
int _toia(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(i_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _exitkangu(i_t *);
int _cdkangu(i_t *);
int usaidizi(i_t *);

/* toem_builtin1.c */
int historia(i_t *);
int _myalias(i_t *);

/*toem_pataline.c */
ssize_t get_input(i_t *);
int _pataline(i_t *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clear_info(i_t *);
void set_info(i_t *, char **);
void free_info(i_t *, int);

/* toem_environ.c */
char *_getenv(i_t *, const char *);
int _envkangu(i_t *);
int _setenvkangu(i_t *);
int _myunsetenv(i_t *);
int p_e_l(i_t *);

/* toem_getenv.c */
char **get_environ(i_t *);
int _unsetenvkangu(i_t *, char *);
int _setenv(i_t *, char *, char *);

/* toem_history.c */
char *get_history_file(i_t *info);
int andika_history(i_t *info);
int soma_history(i_t *info);
int build_history_list(i_t *info, char *buf, int linecount);
int renumber_history(i_t *info);

/* toem_lists.c */
l_t *add_node(l_t **, const char *, int);
l_t *add_node_end(l_t **, const char *, int);
size_t p_l_str(const l_t *);
int delete_node_at_index(l_t **, unsigned int);
void free_list(l_t **);

/* toem_lists1.c */
size_t l_l(const l_t *);
char **l_to_strings(l_t *);
size_t p_l(const l_t *);
l_t *node_with_starts(l_t *, char *, char);
ssize_t g_n_i(l_t *, l_t *);

/* toem_vars.c */
int is_chain(i_t *, char *, size_t *);
void c_c(i_t *, char *, size_t *, size_t, size_t);
int replace_alias(i_t *);
int r_v(i_t *);
int r_s(char **, char *);

#endif
