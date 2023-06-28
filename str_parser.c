#include "main.h"
#include <string.h>
/**
 * parse_data - Function to parse the data obtained from getline
 * @input_str: User input string
 * Return: Tokenized values as an array of strings
 */
char **parse_data(char *input_str)
{
	const char *delimiter = " \n\t\r";
	char *token;
	char **tokens;
	size_t token_count = 0;
	size_t token_len = 0;

	tokens = malloc(sizeof(char *) * (token_count + 5));
	if (tokens == NULL)
	{
		free_tokens(tokens);
		return (NULL);
	}
	token = strtok(input_str, delimiter);
	token_len = _strlen(token);
	while (token != NULL)
	{
		tokens[token_count] = malloc(token_len + 1);
		if (tokens[token_count] == NULL)
		{
			free_tokens(tokens);
			return (NULL);
		}
		strcpy(tokens[token_count], token);
		token = strtok(NULL, delimiter);
		if (token != NULL)
		{
			token_len = _strlen(token);
		}
		token_count++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}

/**
 * free_tokens - Function to free the tokens array
 * @tokens: Pointer to an array of strings (tokens)
 * Return: None
 */
void free_tokens(char **tokens)
{
	int i = 0;

	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
