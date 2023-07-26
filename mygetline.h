#ifndef MYGETLINE_H
#define MYGETLINE_H

#include <stdio.h>

ssize_t mygetline(char **lineptr, FILE *stream);
ssize_t getline_file(char **lineptr, FILE *stream);
#endif /* MYGETLINE_H */

