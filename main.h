#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
void execute_command(char *command, char *program_name);
char **get_path(void);
void prompt_display(void);
char *input_read(void);
void command_execute(char *command, char *program_name);
int main(int argc, char *argv[]);
void displayShellPrompt(void);
char *readUserInput(void);
void executeCommand(char *command, char *program_name);
#endif
