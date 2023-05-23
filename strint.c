#include "main.h"

/**
  * tens_holder - finds the mulitiplication factor of tens
  * @x: the index of the number in the string
  * @z: the string pointer
  *
  * Return: returns the value of the tens multiplier
  */

int tens_holder(int x, char *z)
{
	double tens = 1;

	while (z[x] >= '0' && z[x] <= '9')
	{
		tens *= 10;
		x++;
	}

	tens /= 10;

	return ((int) tens);
}

/**
  * to_integer - gets an integer from a string
  * @y: the string that is converted
  *
  * Return: returns the converted value
  */

int to_integer(char *y)
{
	int x, z = 0;
	int tens = 1;
	unsigned int number = 0;
	int negative = 0;
	int neg_number = 0;
	int positive_num = 0;

	while (y[z] != '\0')
	{
		if (y[z] > '9' || y[z] < '0')
			return (-1);
		y++;
	}

	while ((y[x] > '9' || y[x] < '0') && y[x] != '\0')
	{
		if (y[x] == '-')
			neg_number++;
		if (y[x] == '+')
			positive_num++;

		x++;
	}

	if (y[z] == '\0')
		return (0);

	if ((neg_number % 2) != 0)
		negative = 1;

	tens = tens_holder(x, y);
	while (s[x] >= '0' && s[x] <= '9')
	{
		number += ((s[x] - '0') * tens);
		tens /= 10;
		x++;
	}
	if (negative == 1)
		number *= -1;
	return ((int) number);
}

/**
  * prints_integer - prints an integer
  *
  * @value: the number that is converted to a string
  * Return: returns the number of characters printed out
  */

char *prints_integer(int value)
{
	int tens_int = value;
	char *number;
	int tens = 1;
	int x = 0;

	number = malloc(33);

	if (number == NULL)
		return (NULL);

	if (value == 0)
	{
		number[x] = 0 + '0';
		return (number);

	}

	value = value / 10;
	while (value != 0)
	{
		value = value / 10;
		tens *= 10;
	}

	while (tens != 0)
	{
		number[x] = (tens_int / tens) + '0';
		tens_int = tens_int % tens;
		tens /= 10;
		x++;
	}

	number[x] = '\0';
	return (number);
}
