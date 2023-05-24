#include "main.h"

/**
 * _putchar - function that writes a character to std output
 * @c: char to be printed
 * Return: 1 if success
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
