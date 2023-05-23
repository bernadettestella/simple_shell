#include "main.h"

/**
  * command_prompt - prints the prompt to input a command
  *
  * Return: has no resturn value
  */

void command_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);

}
