#include <string.h>
#include "shell.h"

void tokenize_command(char *command, char **args, int max_args)
{
    char *token;
    int arg_index = 0;

    /* Get the first token */
    token = strtok(command, " \t\n");

    /* Walk through other tokens */
    while (token != NULL && arg_index < max_args - 1)
    {
        args[arg_index] = token;
        arg_index++;
        token = strtok(NULL, " \t\n");
    }

    args[arg_index] = NULL; /* Null-terminate the argument list */
}

