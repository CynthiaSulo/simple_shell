#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

extern char **environ;

/* Function prototypes */
char *_strchr(char *s, char c);
int _strcmp(const char *s1, const char *s2);
size_t _strlen(const char *str);
char *fetch_env(char *name);
char *resolve_path(char *command);
void execute_command(char **arguments);
char **parse_data(char *str);
void free_tokens(char **tokens);
int str_length(char *str);
char *str_copy(char *dest, char *src);
int str_compare(char *str1, char *str2);
char *str_find(char *str, char c);
char *str_concat(char *dest, char *src);
int _str_length(char *str);
void handle_sigint(int signum);
char **parse_input(char *input);
void execute_input(char **input);
void free_parsed_input(char **input);
char *read_line(int *end_of_file);
char *remove_comment(char *input_str);
char *_strdup(char *src);

#endif
