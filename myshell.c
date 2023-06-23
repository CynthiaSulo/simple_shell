#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * prompt_display - Displays the shell prompt
 */
void prompt_display(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}

/**
 * input_read - Reads a line of input from the user
 *
 * Return: The input line as a string
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

#define MAX_ARGUMENTS 10

/**
 * executeCommand - Executes the given command
 * @command: The command to execute
 * @program_name: The name of the program
 */
void executeCommand(char *command, char *program_name)
{
	int i;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		char *arguments[MAX_ARGUMENTS];

		arguments[0] = strtok(command, " \n");
		i = 1;

		while (i < MAX_ARGUMENTS - 1 && (arguments[i] = strtok(NULL, " \n")) != NULL)
			i++;
		arguments[i] = NULL;

		execvp(arguments[0], arguments);
		perror(program_name);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		wait(&status);

		if (strcmp(command, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
	}
}
/**
 * _getpath - Retrieves the full path of a command
 * @command: The command to resolve
 *
 * Return: The full path of the command if found, NULL otherwise
 */
char *_getpath(char *command)
{
	char *path = getenv("PATH");
	char *token;
	char *command_path = NULL;

	token = strtok(path, ":");
	while (token != NULL)
	{
		char *temp = malloc(strlen(token) + strlen(command) + 2);

		sprintf(temp, "%s/%s", token, command);
		if (access(temp, F_OK) == 0)
		{
			command_path = temp;
			break;
		}
		free(temp);
		token = strtok(NULL, ":");
	}
	return (command_path);
}
/**
  * main - Entry point of Shell Program
  *
  * Return: 0 on Sucess
  */
int main(void)
{
	char *line;

	while (1)
	{
		prompt_display();
		line = input_read();
		line[strcspn(line, "\n")] = '\0';
		if (strlen(line) > 0)
		{
			if (strncmp(line, "exit", 4) == 0)
			{
				executeCommand(line, "shell");
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
					executeCommand(line, "shell");
				}
				else
				{
					perror("shell");
				}
			}
			else
			{
				executeCommand(line, "shell");
			}
		}
		free(line);
	}

	return (0);
}
