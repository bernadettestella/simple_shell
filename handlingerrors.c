#include "main.h"

/**
 * _erratoi - a function that transforms a string to an integer
 * @st: string
 * Return: converted number, -1 on error or 0 if no numbers in string
 */

int _erratoi(char *st)
{
	int x = 0;
	unsigned long int results = 0;

	if (*st == '+')
		st++;
	for (x = 0;  st[x] != '\0'; x++)
	{
		if (st[x] >= '0' && st[x] <= '9')
		{
			results *= 10;
			results += (st[x] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}

/**
 * print_error - a function that displays an error message
 * @information: a structure
 * @str: string
 * Return: converted number, -1 on error or 0 if no numbers in string
 */

void print_error(info_t *information,  char *str)
{
	_eputs(information->fname);
	_eputs(": ");
	print_d(information->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(information->argv[0]);
	_eputs(": ");
	_eputs(str);
}

/**
 * print_d - a function that prints a decimal integer (base 10)
 * @inputs: input by user
 * @fd: file descriptor
 * Return: number of characters printed
 */

int print_d(int inputs, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, counts = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (inputs < 0)
	{
		_abs_ = -inputs;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = inputs;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			counts++;
		}
		current %= x;
	}
	__putchar('0' + current);
	counts++;

	return (counts);
}

/**
 * convert_number - a function that convert function similar to atoi
 * @numb: integer used
 * @baze: base of number
 * @flag: flags argument
 * Return: string
 */

char *convert_number(long int numb, int baze, int flag)
{
	static char *arr;
	static char buffer[50];
	char signs = 0;
	char *ptrs;
	unsigned long nl = numb;

	if (!(flag & CONVERT_UNSIGNED) && numb < 0)
	{
		nl = -numb;
		signs = '-';

	}
	arr = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptrs = &buffer[49];
	*ptrs = '\0';

	do	{
		*--ptrs = arr[nl % baze];
		nl /= baze;
	} while (nl != 0);

	if (signs)
		*--ptrs = signs;
	return (ptrs);
}

/**
 * remove_comments - a function that replaces first '#' with '\0'
 * @buff: string address
 * Return: Always 0
 */

void remove_comments(char *buff)
{
	int x;

	for (x = 0; buff[x] != '\0'; x++)
		if (buff[x] == '#' && (!x || buff[x - 1] == ' '))
		{
			buff[x] = '\0';
			break;
		}
}
