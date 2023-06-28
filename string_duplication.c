#include "main.h"

/**
 * _strdup - Creates a duplicate of a string.
 * @src: The source string to duplicate.
 *
 * Return: A pointer to duplicated string, NULL if memory alloc fails.
 */
char *_strdup(char *scr)
{
	size_t i;
	char *dup;

	if (scr == NULL)
	{
		return (NULL);
	}

	dup = malloc(_strlen(scr) + 1);

	if (dup != NULL)
	{
		for (i = 0; i < _strlen(scr); i++)
		{
			dup[i] = scr[i];
		}

		dup[i] = '\0';

		return (dup);
	}
	else
	{
		free(dup);
		return (NULL);
	}
}
