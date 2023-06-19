#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
  *prompt_display - Display the shell prompt
  */
void prompt_display(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
/**
  *input_read - Read a line of input from the user
  *Return: total number of lines
  */
char *input_read(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	chars_read = getline(&line, &bufsize, stdin);

	if (chars_read == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
/**
  *command_execute - execute command
  *@command: pointer to the command to be executed
  *@program_name: pointer to the program name
  */
void command_execute(char *command, char *program_name)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		char *arguments[10];
		char *token;
		int i = 0;

		token = strtok(command, " \t\n");

		while (token != NULL)
		{
			arguments[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		arguments[i] = NULL;

		execve(arguments[0], arguments, environ);
		perror(program_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		wait(&status);

		if (strcmp(command, "exit") == 0)
		{
			return;
		}
	}
}
