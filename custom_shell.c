#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * render_prompt - Displays the shell prompt
 */
void render_prompt(void)
{
	write(STDOUT_FILENO, ":) ", 3);
}

/**
 * retrieve_line - Reads a line of input from the user
 *
 * Return: The input line as a string
 */
char *retrieve_line(void)
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
 * command_execute - Executes the given command
 * @command: The command to execute
 * @program_name: The name of the program
 */
void command_execute(char *command, char *program_name)
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
  * main - Entry point of shell program
  *
  * Return: 0 on success
  */
int main(void)
{
	char *line;

	while (1)
	{
		render_prompt();
		line = retrieve_line();
		line[strcspn(line, "\n")] = '\0';
		if (strlen(line) > 0)
		{
			if (strncmp(line, "exit", 4) == 0)
			{
				command_execute(line, "shell");
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
					command_execute(line, "shell");
				}
				else
				{
					perror("shell");
				}
			}
			else
			{
				command_execute(line, "shell");
			}
		}

		free(line);
	}
	return (0);
}
