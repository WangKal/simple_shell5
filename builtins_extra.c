#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "alias.h"

/* Constants for builtin command return values */
#define BUILTIN_SUCCESS 0
#define BUILTIN_FAILURE 1
#define BUILTIN_EXIT 2
#define BUILTIN_CD 3
#define BUILTIN_ENV 4

/* Execute the env builtin command */
int execute_builtin_env() {
    extern char **environ;

    int i = 0;
    while (environ[i] != NULL) {
        printf("%s\n", environ[i]);
        i++;
    }

    return BUILTIN_SUCCESS;
}

/* Execute the setenv builtin command */
int execute_builtin_setenv(char **args) {
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return BUILTIN_FAILURE;
    }

    if (setenv(args[1], args[2], 1) != 0) {
        fprintf(stderr, "Error: Failed to set environment variable\n");
        return BUILTIN_FAILURE;
    }

    return BUILTIN_SUCCESS;
}

/* Execute the unsetenv builtin command */
int execute_builtin_unsetenv(char **args) {
    if (args[1] == NULL || args[2] != NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return BUILTIN_FAILURE;
    }

    if (unsetenv(args[1]) != 0) {
        fprintf(stderr, "Error: Failed to unset environment variable\n");
        return BUILTIN_FAILURE;
    }

    return BUILTIN_SUCCESS;
}

/* Execute the builtin command */
int execute_builtin_command(char *command, char **args) {
    if (strcmp(command, "exit") == 0) {
        return execute_builtin_exit(args);
    } else if (strcmp(command, "cd") == 0) {
        return execute_builtin_cd(args);
    } else if (strcmp(command, "env") == 0) {
        return execute_builtin_env();
    } else if (strcmp(command, "setenv") == 0) {
        return execute_builtin_setenv(args);
    } else if (strcmp(command, "unsetenv") == 0) {
        return execute_builtin_unsetenv(args);
    } else if (strcmp(command, "alias") == 0) {
        return execute_builtin_alias(args);
    }else {
        fprintf(stderr, "Unknown builtin command: %s\n", command);
        return BUILTIN_FAILURE;
    }
}

