#include "main.h"
/**
 * main - Entry point of the custom shell
 * This function implements a basic shell
 * reads user input, parses it,executes the commands.
 * displays a shell prompt, reads input from the user.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char **arguments;
	char *shell_prompt = "$ ";
	char *user_input = NULL;
	size_t input_size = 0;
	int input_length = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(STDOUT_FILENO, shell_prompt, _strlen(shell_prompt));
		}
		input_length = getline(&user_input, &input_size, stdin);
		if (input_length == -1)
		{
			free(user_input);
			exit(0);
		}
		if (user_input[input_length - 1] == '\n')
		{
			user_input[input_length - 1] = '\0';
		}
		arguments = parse_input(user_input);
		if (arguments != NULL)
		{
			execute_command(arguments);
		}
		free_arguments(arguments);
	}
	free(user_input);
	return (0);
}
