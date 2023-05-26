#include "main.h"

/**
  * _strcpy - copies one string to another
  * @destination: the destination string
  * @source: the source string
  *
  * Return: returns a pointer to the destinantion string
  */

char *_strcpy(char *destination, char *source)
{
	int x = 0;

	if (destination == source || source == 0)
		return (destination);

	while (source[x])
	{
		destination[x] = source[x];
		x++;
	}

	destination[x] = 0;

	return (destination);
}

/**
  * _strdup - duplicates a string
  * @source_string: the string to duplicate
  *
  * Return: returns a pointer to the duplicated string
  */

char *_strdup(const char *source_string)
{
	int len = 0;
	char *ret;

	if (source_string == NULL)
		return (NULL);

	while (*source_string++)
		len++;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);

	for (len++; len--;)
		ret[len] = *--source_string;

	return (ret);
}

/**
  * _puts - prints input from a string
  * @str: the string to be printed
  *
  * Return: has no return value
  */

void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;

	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
  * _putchar - writes c as output
  * @c: the character to be printed
  *
  * Return: returns 1 on success else -1
  */

int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}

	if (c != BUF_FLUSH)
		buf[x++] = c;

	return (1);
}
