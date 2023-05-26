#include "main.h"

/**
  * _strlen - gets the number of characters in a string
  * @s: a pointer to the string being calculated
  *
  * Return: returns the length of the string
  */

int _strlen(char *s)
{
	int x = 0;

	if (!s)
		return (0);

	while (*s++)
		x++;

	return (x);
}

/**
  * _strcmp - compares two strings
  * @string1: the first string
  * @string2: the second string
  *
  * Return: returns a positive, negative or equal value
  */

int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}

	if (*string1 == *string2)
		return (0);

	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
  * starts_with - determines whether set string begins with a substring
  * @home_string: the string that will be searched
  * @seeker: the substring that would be found
  *
  * Return: returns a pointer to the next character after the substring
  */

char *starts_with(const char *home_string, const char *seeker)
{
	while (*seeker)
		if (*seeker++ != *home_string++)
			return (NULL);

	return ((char *)home_string);
}

/**
  * _strcat - appends one string onto another
  * @destination: the destination of the appended string
  * @source: the origin of the appended string
  *
  * Return: returns a pointer to the destination
  */

char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;

	while (*source)
		*destination++ = *source++;

	*destination = *source;

	return (ret);
}
