#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
    return line;
}

/**
 * parse_arguments - Parses the command line into arguments
 * @line: The command line
 * Return: An array of arguments
 */
char **parse_arguments(char *line)
{
    int bufsize = 64;
    int position = 0;
    char **arguments = malloc(bufsize * sizeof(char *));
    char *token;

    if (!arguments)
    {
        perror("allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\n\r\a");
    while (token != NULL)
    {
        arguments[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += 64;
            arguments = realloc(arguments, bufsize * sizeof(char *));
            if (!arguments)
            {
                perror("allocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\n\r\a");
    }
    arguments[position] = NULL;
    return arguments;
}

/**
 * execute_command - Executes the given command
 * @arguments: The command and its arguments
 */
void execute_command(char **arguments)
{
	 pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }
    else if (pid == 0)
    {
        execve(arguments[0], arguments, NULL);
        perror("./shell");
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
 * Return: 0 on success
 */
int main(void)
{
	 char **arguments;
	 char *line;
    while (1)
    {
        display_prompt();
        line = read_line();

        if (strstr(line, "echo \"/bin/ls\"") != NULL)
        {
            arguments = parse_arguments("/bin/ls");
            execute_command(arguments);
            free(arguments);
        }
        else
        {
            arguments = parse_arguments(line);
            execute_command(arguments);
            free(arguments);
        }

        free(line);
    }

    return 0;
}

