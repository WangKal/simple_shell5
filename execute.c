#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100

extern char **environ; /* Declare the environ variable*/

void execute_external_command(char *command, char **args, char **path_dirs, int num_dirs)
{
    char path[MAX_COMMAND_LENGTH];
    int i;

    for (i = 0; i < num_dirs; i++)
    {
        snprintf(path, MAX_COMMAND_LENGTH, "%s/%s", path_dirs[i], command);
        if (access(path, X_OK) == 0)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                execve(path, args, environ);
                fprintf(stderr, "%s: Command execution error\n", args[0]);
                exit(EXIT_FAILURE);
            }
            else if (pid < 0)
            {
                perror("Fork failed");
            }
            else
            {
                wait(NULL);
            }
            return;
        }
    }

    fprintf(stderr, "%s: command not found\n", command);
}

