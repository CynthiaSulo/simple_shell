#include "main.h"

/**
 * read_line - Reads the input string from the user.
 *
 * @end_of_file: Pointer to store the end-of-file indicator.
 * Return: The input string.
 */
char *read_line(int *end_of_file)
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t read_bytes;

	read_bytes = getline(&input, &bufsize, stdin);

	if (read_bytes == -1)
	{
		*end_of_file = 1;
		free(input);
		input = NULL;
		return (NULL);
	}
	if (input[read_bytes - 1] == '\n')
		input[read_bytes - 1] = '\0';

	return (input);
}
