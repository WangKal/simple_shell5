#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> /* Add this header for the wait function */

#define MAX_COMMAND_LENGTH 100

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
    printf("($) "); /* Display the prompt */
    fflush(stdout); /* Flush stdout to ensure prompt is displayed */
}

/**
 * read_command - Reads a command from the user.
 * @command: The buffer to store the command.
 * @size: The size of the buffer.
 *
 * Return: The number of characters read.
 */
ssize_t read_command(char *command, size_t size)
{
    ssize_t nread;

    nread = getline(&command, &size, stdin);
    if (nread == -1)
    {
        printf("\n");
        exit(EXIT_SUCCESS);
    }

    return nread;
}

/**
 * execute_command - Executes the given command using execve.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
    char *args[] = {NULL}; /* We don't need any arguments for programs */
    pid_t pid;
    int status; /* Variable to store the status of the child process */

    extern char **environ; /* Declare environ variable */

    pid = fork();

    if (pid < 0)
    {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        execve(command, args, environ);

        /* If execve returns, an error occurred, print an error message */
        perror("Command execution error");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        /* Wait for the child process to complete */
        wait(&status);

        /* Check if the child process terminated normally */
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            printf("Child process exited with status %d\n", exit_status);
        }
    }
}

/**
 * main - Simple UNIX command line interpreter (shell).
 *
 * Return: Always 0.
 */
int main(void)
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        print_prompt();
        if (read_command(command, sizeof(command)) == -1)
            break;

        /* Remove the trailing newline character from the command */
        command[strcspn(command, "\n")] = '\0';

        execute_command(command);
    }

    return 0;
}

