//header file, all these declarations are shared between other c files

#ifndef MINISH_H
#define MINISH_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//inputhandling
void shell_interactive(void);
void shell_no_interactive(void);

void execute_command(char *line);

int builtin_cd(char **args);
int builtin_env(void);
int handle_builtin(char **args);

#endif