#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * str_length - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string.
 */
int str_length(char *str)
{
	int length = 0;

	if (str != NULL)
	{
		while (*(str + length))
		{
			length++;
		}
	}

	return (length);
}

/**
 * str_copy - Copies a string from source to destination.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *str_copy(char *dest, char *src)
{
	int i = 0;
	int j;

	if (src == NULL)
	{
		return (dest);
	}

	while (*(src + i) != '\0')
	{
		i++;
	}

	for (j = 0; j < i; j++)
	{
		dest[j] = src[j];
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * str_compare - Compares two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0, a negative value, or a positive value
 */
int str_compare(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		return (-1);
	}

	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}

/**
 * str_find - Finds the first occurrence of a character in a string.
 * @str: The input string.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence or NULL
 */
char *str_find(char *str, char c)
{
	if (str == NULL)
	{
		return (NULL);
	}

	while ((*str != c) && (*str != '\0'))
	{
		str++;
	}

	if (*str == c)
	{
		return (str);
	}

	return (NULL);
}

/**
 * str_concat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *str_concat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	if ((src == NULL && dest == NULL) || dest == NULL)
	{
		return (NULL);
	}

	if (src == NULL)
	{
		return (dest);
	}

	while (dest[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}
