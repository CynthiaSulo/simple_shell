#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * present_prompt - Displays the shell prompt
 */
void present_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 3);
}
/**
 * capture_input - Reads a line of input from the user
 * Return: The input line as a string
 */
char *capture_input(void)
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
 * handleExecution- Executes the given command
 * @command: The command to execute
 * @program_name: The name of the program
 */
void handleExecution(char *command, char *program_name)
{
	pid_t pid = fork();

	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		char *arguments[3];

		arguments[0] = command;
		arguments[1] = NULL;

		execve(arguments[0], arguments, environ);
		perror(program_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		wait(&status);
	}
}
/**
 * main - Entry point of the shell program
 * @argc: The argument count
 * @argv: The argument vector
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *line;
	(void)argc;

	while (1)
	{
		present_prompt();

		line = capture_input();
		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) > 0)
		{
			handleExecution(line, argv[0]);
		}
		free(line);
	}
	return (0);
}
