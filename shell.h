#ifndef SHELL_H

#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
extern char **environ;

void command_existence(char *strArr[]);
char *get_command_path(char *command);
char *get_path(void);
void execute_command(char *strArr[]);
void tokenize_string(char *str, char *strArr[]);



#endif
