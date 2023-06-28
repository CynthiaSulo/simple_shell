#include "main.h"

/**
 * remove_comment - Removes comments from the input string.
 *
 * @input_str: The input string.
 * Return: The input string without comments.
 */
char *remove_comment(char *input_str)
{
	int i, last_non_comment;

	last_non_comment = 0;
	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == '#')
		{
			if (i == 0)
			{
				free(input_str);
				return (NULL);
			}
			if (input_str[i - 1] == ' ' ||
					input_str[i - 1] == '\t' ||
					input_str[i - 1] == ';')
				last_non_comment = i;
		}
	}

	if (last_non_comment != 0)
	{
		input_str = realloc(input_str, i, last_non_comment + 1);
		input_str[last_non_comment] = '\0';
	}

	return (input_str);
}

/**
 * shell_loop - Main loop of the shell.
 *
 * @shell_data: Pointer to the shell data structure.
 * Return: No return.
 */
void shell_loop(data_shell *shell_data)
{
	int loop_flag, eof_flag;
	char *user_input;

	loop_flag = 1;
	while (loop_flag == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		user_input = read_line(&eof_flag);
		if (eof_flag != -1)
		{
			user_input = remove_comment(user_input);
			if (user_input == NULL)
				continue;

			if (check_syntax_error(shell_data, user_input) == 1)
			{
				shell_data->status = 2;
				free(user_input);
				continue;
			}
			user_input = replace_variables(user_input, shell_data);
			loop_flag = split_commands(shell_data, user_input);
			shell_data->counter += 1;
			free(user_input);
		}
		else
		{
			loop_flag = 0;
			free(user_input);
		}
	}
}
