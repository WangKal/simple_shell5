#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "execute.h"
#include "builtins.h"

#define MAX_COMMAND_LENGTH 100

void split_commands_by_operator(char *command, char **commands, char *operator) {
    int i = 0;
    char *start = command;

    while (*command != '\0') {
        if (strncmp(command, operator, strlen(operator)) == 0) {
            *command = '\0';
            commands[i++] = start;
            start = command + strlen(operator);
        }
        command++;
    }

    commands[i++] = start;
    commands[i] = NULL;
}

void split_commands_by_semicolon(char *command, char **commands) {
    int i = 0;
    char *start = command;

    while (*command != '\0') {
        if (*command == ';') {
            *command = '\0';
            commands[i++] = start;
            start = command + 1;
        }
        command++;
    }

    commands[i++] = start;
    commands[i] = NULL;
}

void execute_command(char *command, char **path_dirs, int num_dirs) {
    char *commands[MAX_COMMAND_LENGTH];
    int i;
    split_commands_by_semicolon(command, commands);

    i = 0;
    while (commands[i] != NULL) {
        char *args[MAX_COMMAND_LENGTH];
        tokenize_command(commands[i], args, MAX_COMMAND_LENGTH);

        if (args[0] != NULL) {
            if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "env") == 0) {
                execute_builtin_command(args[0], args);
            } else {
                execute_external_command(args[0], args, path_dirs, num_dirs);
            }
        }

        i++;
    }
}

