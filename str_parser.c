#include "main.h"
#include <string.h>
/**
 * parse_input - Function to parse the data obtained from getline
 * @input_str: User input string
 * Return: Tokenized values as an array of strings
 */
char **parse_input(char *input_str)
{
	const char *delimiter = " \n\t\r";
	char *str_token;
	char **arguments;
	size_t token_count = 0;
	size_t length = 0;

	arguments = malloc(sizeof(char *) * (token_count + 5));
	if (arguments == NULL)
	{
		free_arguments(arguments);
		return (NULL);
	}
	str_token = strtok(input_str, delimiter);
	length = _strlen(str_token);
	while (str_token != NULL)
	{
		arguments[token_count] = malloc(length + 1);
		if (arguments[token_count] == NULL)
		{
			free_arguments(arguments);
			return (NULL);
		}
		_strcpy(arguments[token_count], str_token);
		str_token = strtok(NULL, delimiter);
		if (str_token != NULL)
		{
			length = _strlen(str_token);
		}
		token_count++;
	}
	arguments[token_count] = NULL;
	return (arguments);
}

/**
 * free_arguments - Function to free the tokens array
 * @arguments: Pointer to an array of strings (tokens)
 * Return: None
 */
void free_arguments(char **arguments)
{
	int j = 0;

	while (arguments[j] != NULL)
	{
		free(arguments[j]);
		j++;
	}
	free(arguments);
}
