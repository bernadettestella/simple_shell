#include "main.h"

/**
  * _memset - allocates a byte value to a memory
  * @s: pointer to the memory area to be filled
  * @b: the byte value to used to fill the area
  * @j: the number of bytes to be filled
  *
  * Return: returns a pointer to the memory area
  */

char *_memset(char *s, char b, unsigned int j)
{
	unsigned int a;

	for (a = 0; a < j; a++)
		s[a] = b;

	return (s);
}

/**
  * ffree - deallocates an array of strings
  * @pda: pointer to a dynamic array
  *
  * Return: has no return value
  */

void ffree(char **pda)
{
	char **s = pda;

	if (!pda)
		return;

	while (*pda)
		free(*pda++);

	free(s);
}

/**
  * _realloc - modifies previously allocated memory
  * @pointer: points to previously allocated memory
  * @old: size of previous allocation in bytes
  * @new: size of new allocation in bytes
  *
  * Return: returns a pointer to the newly reallocated memory
  */

void *_realloc(void *pointer, unsigned int old, unsigned int new)
{
	char *m;

	if (!pointer)
		return (malloc(new));

	if (!new)
		return (free(pointer), NULL);

	if (new == old)
		return (pointer);

	m = malloc(new);
	if (!m)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		m[old] = ((char *)pointer)[old];

	free(pointer);

	return (m);
}
