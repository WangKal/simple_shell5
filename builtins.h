#ifndef BUILTINS_H
#define BUILTINS_H

int is_builtin_command(const char *command);
int execute_builtin_command(char *command, char **args);
void handle_alias_command(int num_args, char **args);
int execute_builtin_exit(char **args);
int execute_builtin_cd(char **args);
#endif /* BUILTINS_H */

