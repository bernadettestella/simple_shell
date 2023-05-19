#include "main.h"

/**
 * handles-error - a function to help write an error message if file
 * is not found
 * @argv: the array of arguments strings passed to function
 * @arr: an array of tokens entered by user
 * @cmd_count: the number count of commands entered
 * @line: the spcce for user to input
 * @nonline: the user input with no new line character
 */

void handles_error(char **argv, char **arr, char *line, char *nonline,
		int cmd_count)
{
	char *numb;

	numb = prints_integer(cmd_count);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, numb, _strlen(numb));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arr[0], _strlen(arr[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "Not found\n", 10);
	free(numb);
	free_all(line, nonline, arr);
	exit(0);
}
