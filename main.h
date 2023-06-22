#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGUMENTS 10

extern char **environ;

void display_prompt(void);
void execute_command(char *command, char *program_name);
char **get_path(void);
void prompt_display(void);
char *input_read(void);
void command_execute(char *command, char *program_name);
void displayShellPrompt(void);
char *readUserInput(void);
void executeCommand(char *command, char *program_name);
void parse_command(char *line, char **command, char **args);
void find_command(char *command, char **full_path);
char *_getpath(char *command);
/* Shell built-in commands */
int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **args);

/* Utility functions */
void handle_error(const char *msg);
char *read_line(void);
char **split_line(char *line);
int is_builtin(char **args);

#endif
