#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
/*
 *  Constants for the return values of builtin commands
 */
#define BUILTIN_EXIT 0
#define BUILTIN_CD 1
#define BUILTIN_FAILURE 2
#define BUILTIN_SUCCESS 3
#define BUILTIN_ENV 4
#define BUILTIN_EXTERNAL 5

/*
 *  Function prototypes for builtin commands
 */
void set_environment_variable(char *variable, char *value);
void unset_environment_variable(char *variable);

void print_prompt(void);
void tokenize_command(char *command, char **args, int max_args);
void execute_command(char *command, char **path_dirs, int num_dirs);

#endif /* SHELL_H */

