#include "main.h"

/**
  * _strncpy - copies a string
  * @destination: the destination of the copied string
  * @source: the source of the string
  * @f: the number of characters to be copied
  *
  * Return: returns the copied string
  */

char *_strncpy(char *destination, char *source, int f)
{
	int x, z;
	char *s = destination;

	x = 0;
	while (source[x] != '\0' && x < f - 1)
	{
		destination[x] = source[x];
		x++;
	}

	if (x < f)
	{
		z = x;
		while (z < f)
		{
			destination[z] = '\0';
			z++;
		}
	}

	return (s);
}

/**
  * _strncat - concatenates two strings
  * @str_one: the first string
  * @str_two: the second string
  * @f: the number of bytes used
  *
  * Return: returns the concatenated string
  */

char *_strncat(char *str_one, char *str_two, int f)
{
	int x, z;
	char *s = str_one;

	x = 0;
	z = 0;
	while (str_one[x] != '\0')
		x++;

	while (str_two[z] != '\0' && z < f)
	{
		str_one[x] = str_two[z];
		x++;
		z++;
	}

	if (z < f)
		str_one[x] = '\0';

	return (s);
}

/**
  * _strchr - looks for a character in a string
  * @s: the string in question
  * @v: the character to look for
  *
  * Return: returns a pointer to the memory pointer in s
  */

char *_strchr(char *s, char v)
{
	do {
		if (*s == v)
			return (s);

	}
	while (*s++ != '\0');

	return (NULL);

}
