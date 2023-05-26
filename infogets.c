#include "main.h"

/**
 * clear_info - a function with a structure that  holds potential arguments
 * @information: the address of the structure created
 */

void clear_info(info_t *information)

{
	information->arg = NULL;
	information->argv = NULL;
	information->path = NULL;
	information->argc = 0;
}

/**
 * set_info - a function that initializes info_t struct
 * @information: struct address
 * @vector: argument vector
 */
void set_info(info_t *information, char **vector)
{
	int x = 0;

	information->fname = vector[0];
	if (information->arg)
	{
		information->argv = strtow(information->arg, " \t");
		if (!information->argv)
		{

			information->argv = malloc(sizeof(char *) * 2);
			if (information->argv)
			{
				information->argv[0] = _strdup(information->arg);
				information->argv[1] = NULL;
			}
		}
		for (x = 0; information->argv && information->argv[x]; x++)
			;
		information->argc = x;

		replace_alias(information);
		replace_vars(information);
	}
}

/**
 * free_info - a function that frees info_t struct fields
 * @information: address
 * @alls: true if freeing all fields
 */
void free_info(info_t *information, int alls)
{
	ffree(information->argv);
	information->argv = NULL;
	information->path = NULL;
	if (alls)
	{
		if (!information->cmd_buf)
			free(information->arg);
		if (information->env)
			free_list(&(information->env));
		if (information->history)
			free_list(&(information->history));
		if (information->alias)
			free_list(&(information->alias));
		ffree(information->environ);
			information->environ = NULL;
		bfree((void **)information->cmd_buf);
		if (information->readfd > 2)
			close(information->readfd);
		_putchar(BUF_FLUSH);
	}
}
