#include "main.h"

/**
 *_eputs - a function that prints an input string
 * @st: string
 * Return: Nothing
 */

void _eputs(char *st)
{
	int x = 0;

	if (!st)
		return;
	while (st[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - a function that outputs the character c to the standard
 * error stream (stderr)
 * @ch: character
 * Return: On success 1 on error, -1 is returned or errno is set appropriately.
 */

int _eputchar(char ch)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}

/**
 * _putfd - a function writes the character 'ch' to the specified
 * file descriptor (fd)
 * @ch: character
 * @fd: file descriptor
 * Return: On success 1 on error, -1 is returned or errno is set appropriately.
 */

int _putfd(char ch, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}

/**
 *_putsfd - a function  displays an input string
 * @st: string
 * @fd: file descriptor
 * Return: the number of chars put
 */
int _putsfd(char *st, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*st)
	{
		x += _putfd(*st++, fd);
	}
	return (x);
}
