#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}
/**
 * read_line - Reads a line of input from the user
 * Return: The input line as a string
 */
char *read_line(void)
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
 * execute_command - Executes the given command
 * @command: The command to execute
 * @program_name: The name of the program
 */
void execute_command(char *command, char *program_name)
{
	pid_t pid = fork();

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

		if (strcmp(command, "exit") == 0)
		{
			return;
		}
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
		display_prompt();

		line = read_line();

		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) > 0)
		{
			execute_command(line, argv[0]);
		}

		free(line);
	}
	return (0);
}
