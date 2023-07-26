#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

#define BUFFER_SIZE 1024

ssize_t mygetline(char **lineptr, FILE *stream) {
    size_t bufsize = 0;
    ssize_t ret;

    if (stream == stdin) {
        ret = getline(lineptr, &bufsize, stdin);
    } else {
        char *line = NULL;
        size_t len = 0;

        while ((ret = getline(&line, &len, stream)) != -1) {
            if (line[ret - 1] == '\n') {
                line[ret - 1] = '\0'; /* Remove newline character if present */
            }
            *lineptr = line;
            break;
        }
    }

    return ret;
}
/* Function to read a line from a file stream and store it in lineptr */
ssize_t getline_file(char **lineptr, FILE *stream) {
    size_t bufsize = 0; /* Initial buffer size set to 0 for getline to allocate*/
    ssize_t ret = getline(lineptr, &bufsize, stream);
    return ret;
}
