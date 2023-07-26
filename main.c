#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "path.h"
#include "mygetline.h"
#include "print_environment.h"
#define MAX_PATH_DIRS 100

int main(void)
{
    char *command = NULL;
    ssize_t ret;
    char *path_dirs[MAX_PATH_DIRS];
    int num_dirs;

    /* Get the PATH environment variable */
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not set.\n");
        return EXIT_FAILURE;
    }

    /* Tokenize the PATH environment variable into individual directories */
    
    num_dirs = tokenize_path(path_env, path_dirs);

    while (1)
    {
        print_prompt();

        /* Read the command from the user */
        ret = mygetline(&command, stdin);
        if (ret == -1)
        {
            /* End of file or error in reading input, exit the shell */
            free(command);
            break;
        }

        /* Execute the command */
        execute_command(command, path_dirs, num_dirs);

        /* Free the dynamically allocated command buffer */
        free(command);
    }

    /* Free the path directories */
    free_path_dirs(path_dirs, num_dirs);

    return EXIT_SUCCESS;
}

