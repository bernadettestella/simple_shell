#include "main.h"

/**
  * strtow - divides a string into individual characters
  * @str: the string to be split
  * @d: the delimiter used to split the words
  *
  * Return: an array to the individual words else NULL
  */

char **strtow(char *str, char *d)
{
	int x, l, b, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!d)
		d = " ";

	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str
					[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, l = 0; l < numwords; l++)
	{
		while (is_delim(str[x], d))
			x++;
		b = 0;
		while (!is_delim(str[x + b], d) && str[x + b])
			b++;
		s[l] = malloc((b + 1) * sizeof(char));
		if (!s[l])
		{
			for (b = 0; b < l; b++)
				free(s[b]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < b; e++)
			s[l][e] = str[x++];
		s[l][e] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
  * strtow2 - splits a string based on a specific delimiter
  * @str: the string to be split
  * @d: the delimiter that separates characters in a string
  *
  * Return: an array that strings that rep. individual characters else NULL
  */

char **strtow2(char *str, char d)
{
	int x, l, b, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			numwords++;

	if (numwords == 0)
		return (NULL);

	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	for (x = 0, l = 0; l < numwords; l++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		b = 0;
		while (str[x + b] != d && str[x + b] && str[x + b] != d)
			b++;

		s[l] = malloc((b + 1) * sizeof(char));
		if (!s[l])
		{
			for (b = 0; b < l; b++)
				free(s[b]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < b; e++)
			s[l][e] = str[x++];
		s[l][e] = 0;
	}
	s[l] = NULL;
	return (s);
}
