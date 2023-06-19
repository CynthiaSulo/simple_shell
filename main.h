#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
void execute_command(char *command, char *program_name);
char **get_path(void);

#endif
