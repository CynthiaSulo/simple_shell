#include "main.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * fetch_env - searches for the value of an environment variable
 * @name: name of the environment variable
 * Return: Value of the environment variable
 */
char *fetch_env(char *name)
{
	int idx = 0;
	char *env_value;
	char *env_entry;

	if (name == NULL)
		return (NULL);

	env_entry = environ[idx];
	while (env_entry != NULL)
	{
		if (_strcmp(env_entry, name) == 0)
		{
			env_value = _strchr(env_entry, '=');
			if (env_value == NULL)
				return (NULL);
			return (env_value + 1);
		}
		idx++;
	}

	return (NULL);
}

/**
 * resolve_path - retrieves the location of the executable file thus resolving
 * @command: command name
 * Return: Path of the executable file
 */
char *resolve_path(char *command)
{
	char *file_path = NULL;
	char *filepath_copy = NULL;
	char *path_token = NULL;
	char *search_path = NULL;
	const char *delim = ":";
	struct stat buffer;

	if (command == NULL)
		return (NULL);
	if (_strchr(command, '/') != NULL || _strchr(command, '.') != NULL)
	{
		if ((stat(command, &buffer) == 0) && (access(command, X_OK) == 0))
		{
			return (_strdup(command));
		}
		return (NULL);
	}
	file_path = getenv("PATH");
	filepath_copy = _strdup(file_path);
	if (file_path == NULL)
		return (NULL);
	path_token = strtok(filepath_copy, delim);
	while (path_token != NULL)
	{
		search_path = malloc(_strlen(path_token) + _strlen(command) + 2);
		if (search_path == NULL)
			return (NULL);
		strcpy(search_path, path_token);
		strcat(search_path, "/");
		strcat(search_path, command);
		if ((access(search_path, X_OK) == 0) && (stat(search_path, &buffer) == 0))
		{
			free(filepath_copy);
			return (search_path);
		}
		free(search_path);
		path_token = strtok(NULL, delim);
	}
	free(filepath_copy);
	return (NULL);
}
/**
 * execute_command - replaces the child process with a new program
 * @arguments: array of command arguments
 * Return: nothing
 */
void execute_command(char **arguments)
{
	pid_t child_pid;
	int status = 0;
	char *executable_path = NULL;
	char *error_msg = "Command not found: ";

	if (arguments == NULL)
		return;

	executable_path = resolve_path(arguments[0]);
	if (executable_path == NULL)
	{
		write(STDERR_FILENO, error_msg, _strlen(error_msg));
		write(STDERR_FILENO, arguments[0], _strlen(arguments[0]));
		write(STDERR_FILENO, "\n", 1);
		return;
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("child");
		exit(0);
	}
	else if (child_pid == 0)
	{
		if (execve(executable_path, arguments, environ) == -1)
		{
			perror("execve");
			exit(0);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			exit(0);
		}
	}
	free(executable_path);
}
