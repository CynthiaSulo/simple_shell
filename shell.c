#include "main.h"

/**
 * main - Entry point of the custom shell
 * This function implements a basic shell
 * reads user input, parses it,executes the commands.
 * displays a shell prompt, reads input from the user
 * processes it until an interrupt signal is received.
 *
 * Return: Always returns 0.
 */
int main(void)
{
	char *shell_prompt = "$ ";
	char **parsed_input;
	char *user_input = NULL;
	int input_length;
	int signal_flag = 0;
	size_t input_size = 0;

	signal(SIGINT, handle_sigint);

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(STDOUT_FILENO, shell_prompt, _str_length(shell_prompt));
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
		if (signal_flag)
		{
			free(user_input);
			break;
		}
		parsed_input = parse_input(user_input);
		if (parsed_input != NULL)
		{
			execute_input(parsed_input);
		}
		free_parsed_input(parsed_input);
	}
	free(user_input);
	return (0);
}
