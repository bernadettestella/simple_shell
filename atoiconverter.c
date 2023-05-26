#include "main.h"

/**
 * interactive - a function thatt checksIf shell is in interactive mode
 * @information: a pointer to a structure of type "info_t".
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */

int interactive(info_t *information)
{
	return (isatty(STDIN_FILENO) && information->readfd <= 2);
}

/**
 * is_delim - a function that checks if characters are delimiters
 * @ch: the character to be checked
 * @delimiter: the string made of delimiters
 * Return: 1 if character is delimiter 0 if otherwise
 */

int is_delim(char ch, char *delimiter)
{
	while (*delimeter)
		if (*delimeter++ == ch)
			return (1);
	return (0);
}

/**
 * _isalpha - a function checks whether a character is alphabetic
 * @ch: The character to be checked
 * Return: 1 if the input character is an alphabetic character, 0 otherwise.
*/

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - a function that converts a string to an integer.
 * @st: The string to be converted.
 *
 * Return: 0 if no numbers in the string else 1
 */
int _atoi(char *st)
{
	int x, signs = 1, flag = 0, output;
	unsigned int result = 0;

	for (x = 0;  st[i] != '\0' && flag != 2; x++)
	{
		if (st[x] == '-')
			signs *= -1;

		if (st[x] >= '0' && st[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (st[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (signs == -1)
		output = -result;
	else
		output = result;

	return (output);
}
