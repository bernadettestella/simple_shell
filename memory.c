#include "main.h"

/**
  * bfree - deallocates the memory allocated and sets it to null
  * @mem: the memory to be deallocated
  *
  * Return: returns 1 if successful else return 0
  */

int bfree(void **mem)
{
	if (mem && *mem)
	{
		free(*mem);
		*mem = NULL;
		return (1);
	}

	return (0);
}
