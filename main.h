#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

extern char **environ;
char **parse_input(char *input_str);
char *fetch_env(char *name);
char *resolve_path(char *command);
void execute_command(char **arguments);
int _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *str1, char *str2);
char *_strchr(char *str, char ch);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
void free_arguments(char **arguments);
#endif /* MAIN_H */
