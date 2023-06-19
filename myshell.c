#include "main.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * displayShellPrompt - Display the shell prompt
 */
void displayShellPrompt(void)
{
    write(STDOUT_FILENO, ":) ", 4);
}

/**
 * readUserInput - reads line of input from the user
 * Return: total number of lines
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
    return line;
}

/**
 * executeCommand - Execute command
 * @command: Pointer to the command to be executed
 * @program_name: Pointer to the program name
 */
void executeCommand(char *command, char *program_name)
{
    char *path = getenv("PATH");
    char *token;
    char *full_path;
    int found = 0;
    pid_t pid;

    token = strtok(path, ":");

    while (token != NULL)
    {
        full_path = malloc(strlen(token) + strlen(command) + 2);
        sprintf(full_path, "%s/%s", token, command);

        if (access(full_path, X_OK) == 0)
        {
            found = 1;
            break;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    if (!found)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", program_name, command);
        return;
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        char *arguments[10];
        int i = 0;

        token = strtok(command, " \t\n");

        while (token != NULL)
        {
            arguments[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        arguments[i] = NULL;

        execve(full_path, arguments, environ);
        perror(program_name);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        wait(&status);
    }

    free(full_path);
}
/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: Exit status
 */
int main(int argc, char *argv[])
{
    char *line;

    (void)argc;

    while (1)
    {
        displayShellPrompt();
        line = readUserInput();

        if (strlen(line) > 0)
        {
            char *command_with_path = NULL;
            char *token;
            char *path = getenv("PATH");
            char *path_copy = strdup(path);

            token = strtok(path_copy, ":");

            while (token != NULL)
            {
                command_with_path = malloc(strlen(token) + strlen(line) + 2);
                sprintf(command_with_path, "%s/%s", token, line);

                if (access(command_with_path, X_OK) == 0)
                {
                    executeCommand(command_with_path, argv[0]);
                    break;
                }

                free(command_with_path);
                command_with_path = NULL;
                token = strtok(NULL, ":");
            }

            free(path_copy);

            if (command_with_path == NULL)
            {
                fprintf(stderr, "%s: 1: %s: not found\n", argv[0], line);
            }
        }

        free(line);
    }

    return 0;
}
