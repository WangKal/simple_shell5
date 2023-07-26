#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Constants for builtin command return values */
#define BUILTIN_SUCCESS 0
#define BUILTIN_FAILURE 1
#define BUILTIN_EXIT 2
#define BUILTIN_CD 3
#define BUILTIN_ENV 4
/* Execute the exit builtin command */
int execute_builtin_exit(char **args) {
    int status = 0;
    if (args[1] != NULL) {
        status = atoi(args[1]);
    }
    exit(status);
}

/* Execute the cd builtin command */
int execute_builtin_cd(char **args) {
    char *cwd;
    char *new_dir;
    if (args[2] != NULL) {
        fprintf(stderr, "Usage: cd [DIRECTORY]\n");
        return BUILTIN_FAILURE;
    }

    new_dir = args[1];

    if (new_dir == NULL) {
        new_dir = getenv("HOME");
    } else if (strcmp(new_dir, "-") == 0) {
        new_dir = getenv("OLDPWD");
        if (new_dir == NULL) {
            fprintf(stderr, "Error: OLDPWD environment variable not set\n");
            return BUILTIN_FAILURE;
        }
    }

    cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        fprintf(stderr, "Error: Failed to get current working directory\n");
        return BUILTIN_FAILURE;
    }

    setenv("OLDPWD", cwd, 1);
    free(cwd);

    if (chdir(new_dir) != 0) {
        fprintf(stderr, "Error: Failed to change directory to %s\n", new_dir);
        return BUILTIN_FAILURE;
    }

    cwd = getcwd(NULL, 0);
    if (cwd == NULL) {
        fprintf(stderr, "Error: Failed to get current working directory\n");
        return BUILTIN_FAILURE;
    }

    setenv("PWD", cwd, 1);
    free(cwd);

    return BUILTIN_SUCCESS;
}

