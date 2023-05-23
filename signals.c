#include "main.h"

/**
  * handles_ctrlc - handles the signal in ctrlc
  * @signal_number: the value of the signal released
  *
  * Return: has no return value
  *
  */

void handles_ctrlc(int signal_number)
{
	(void)signal_number;

	write(STDOUT_FILENO, "\n$ ", 3);

}

/**
  * handles_ctrld - handles the signals in ctrld
  * @input: the buffer that requires freeing
  *
  * Return: has no return value
  */

int handles_ctrld(char *input)
{
	free(input);

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "\n", 1);

	return (0);

}
