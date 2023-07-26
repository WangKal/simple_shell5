#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_DIRS 100 /* Define the maximum number of path directories*/

#include "shell.h" /* Include the shell.h header file*/

int tokenize_path(char *path_env, char **path_dirs)
{
    char *token;
    int dir_index = 0;

   /* Get the first token*/
    token = strtok(path_env, ":");

    /* Walk through other tokens*/
    while (token != NULL && dir_index < MAX_PATH_DIRS - 1)
    {
        path_dirs[dir_index] = token;
        dir_index++;
        token = strtok(NULL, ":");
    }

    path_dirs[dir_index] = NULL; /* Null-terminate the path directories list*/

    return dir_index; /* Return the number of directories*/
}

void free_path_dirs(char **path_dirs, int num_dirs)
{
	int i;
    for (i = 0; i < num_dirs; i++)
    {
        free(path_dirs[i]);
    }
}

