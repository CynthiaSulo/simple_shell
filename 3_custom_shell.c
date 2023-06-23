#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/**
 * exhibit_prompt - Displays the shell prompt
 */
void exhibit_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 3);
}
/**
 * readUserInput - Reads a line of input from the user
 * Return: The input line as a string
 */
char *readUserInput(void)
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
 * print_environment - Prints the current environment
 */
void print_environment(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
/**
 * runCommand - Executes the given command
 * @command: The command to execute
 * @program_name: The name of the program
 */
void runCommand(char *command, char *program_name)
{
	pid_t pid = fork();

	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "env") == 0)
	{
		print_environment();
		return;
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
 * main - Entry point of shell program
 * Return: 0 on success
 */
int main(void)
{
	char *line;

	while (1)
	{
		exhibit_prompt();
		line = readUserInput();
		line[strcspn(line, "\n")] = '\0';

		if (strlen(line) > 0)
		{
			if (strncmp(line, "exit", 4) == 0)
			{
				runCommand(line, "shell");
			}
			else if (strncmp(line, "cd", 2) == 0)
			{
				if (chdir(line + 3) != 0)
				{
					perror("shell");
				}
			}
			else if (line[0] == '/')
			{
				if (access(line, F_OK) == 0)
				{
					runCommand(line, "shell");
				}
				else
				{
					perror("shell");
				}
			}
			else
			{
				runCommand(line, "shell");
			}
		}
		free(line);
	}
	return (0);
}

