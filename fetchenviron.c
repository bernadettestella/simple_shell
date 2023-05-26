#include "main.h"

/**
 * get_environ - a function that returns a copied string arr of env var
 * @information: a structure
 * Return: Always 0
 */

char **get_environ(info_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_to_strings(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}

/**
 * _unsetenv - a function that eliminates environ variable
 * @variab: the environment string
 * @information: a structure
 * Return: 1 upon  delete, 0 if otherwise
 */

int _unsetenv(info_t *information, char *variab)
{
	list_t *node = information->env;
	size_t x = 0;
	char *b;

	if (!node || !variab)
		return (0);

	while (node)
	{
		b = starts_with(node->str, variab);
		if (b && *b == '=')
		{
			information->env_changed =
				delete_node_at_index(&(information->env), x);
			x = 0;
			node = information->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (information->env_changed);
}

/**
 * _setenv - a function that create a new environment variable
 * or alter an existing one
 * @information: a structure
 * @variab: Property name of the environment variable as a string.
 * @val: Value of the environment variable as a string
 *Return: Always 0
 */

int _setenv(info_t *information, char *variab, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *b;

	if (!variab || !val)
		return (0);

	buf = malloc(_strlen(variab) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, variab);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = information->env;
	while (node)
	{
		b = starts_with(node->str, variab);
		if (b && *b == '=')
		{
			free(node->str);
			node->str = buf;
			information->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(information->env), buf, 0);
	free(buf);
	information->env_changed = 1;
	return (0);
}
