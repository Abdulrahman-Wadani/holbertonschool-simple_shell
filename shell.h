#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int tokenize(char *line, char **argv, int max);
void execute_command(char **argv);

#endif /* SHELL_H */
