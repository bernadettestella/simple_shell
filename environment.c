#include "main.h"

/**
 * _myenv - a function that prints the current environment
 * @information: the structure
 * Return: Always 0
 */
int _myenv(info_t *information)
{
	print_list_str(information->env);
	return (0);
}

/**
 * _getenv - a function that fetches the value of an env variable
 * @information: a structure
 * @call: name of the variable
 * Return: the value
 */
char *_getenv(info_t *information, const char *call)
{
	list_t *node = information->env;
	char *b;

	while (node)
	{
		b = starts_with(node->str, call);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function that set up a new environment variable
 *	or update an existing one
 * @information: a struct
 * Return: Always 0
 */

int _mysetenv(info_t *information)
{
	if (information->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a funtion that alter the statement to:
 * Delete an environmental variable
 * @information: a structure
 * Return: Always 0
 */

int _myunsetenv(info_t *information)
{
	int x;

	if (information->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (x = 1; x <= information->argc; x++)
		_unsetenv(information, information->argv[x]);

	return (0);
}

/**
 * populate_env_list - Fills up the linked list for environment variables.
 *
 * @information: a structure
 *
 * Return: Always 0
 */
int populate_env_list(info_t *information)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		add_node_end(&node, environ[x], 0);
	information->env = node;
	return (0);
}
