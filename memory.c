#include "main.h"

/**
  * _reallocate - realloactes the memory allocated to char
  * @pointer: a pointer to an array
  *
  * Return: returns the pointer to new memory allocated
  */

char *_reallocate(char *pointer)
{
	int x = 0;
	char *new_pointer;

	if (pointer == NULL)
		return (NULL);

	while (*(pointer + x) != '\n')
		x++;

	new_pointer = malloc(sizeof(char) * x + 1);
	if (new_pointer == NULL)
		return (NULL);

	x = 0;
	while (*(pointer + x) != '\n')
	{
		*(new_pointer + x) = *(pointer + x);
		x++;
	}
	*(new_pointer + x) = '\0';

	return (new_pointer);

}

/**
  * freelist - frees a list in linked_t
  * @start: the beginning of the linked lists
  *
  * Return: has no return value
  */

void freelist(linked_t *start)
{
	linked_t *next_node;

	while (start != NULL)
	{
		next_node = start->next;
		free(start->directory);
		free(start);

		start = next_node;
	}
}

/**
  * freetokens - frees the tokens in the given array
  * @t_array: an array of tokens
  *
  * Return: has no return value
  */

void freetokens(char **t_array)
{
	int x = 0;

	while (t_array[x] != NULL)
	{
		free(t_array[x]);
		x++;
	}
	free(t_array[x]);
}

/**
  * all_free - frees all the varaibles used
  * @line: the original entered
  * @newline: input without a newline character
  * @arr: an array of tokens
  *
  * Return: has no return value
  */

void all_free(char **line, char *newline, char **arr)
{
	freetokens(arr);
	free(line);
	free(newline);
	free(arr);

}
