#include "main.h"

/**
 * _strdup - Creates a duplicate of a string.
 * @str: The source string to duplicate.
 *
 * Return: A pointer to duplicated string, NULL if memory alloc fails.
 */
char *_strdup(char *str)
{
	char *dup;
	int j;

	if (str == NULL)
	{
		return (NULL);
	}

	dup = malloc(_strlen(str) + 1);

	if (dup != NULL)
	{
		for (j = 0; j < _strlen(str); j++)
		{
			dup[j] = str[j];
		}

		dup[j] = '\0';

		return (dup);
	}
	else
	{
		free(dup);
		return (NULL);
	}
}
