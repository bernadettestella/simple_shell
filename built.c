#include "main.h"

/**
 * _myhistory - a function displays the history list, one command per line,
 * with line numbers
 * @information: structure that holds possible arguments and is utilized
 * to ensure that the function prototype remains constant
 * Return: Always 0
 */
int _myhistory(info_t *information)
{
	print_list(information->history);
	return (0);
}

/**
 * unset_alias - a function that adds alias to string is set
 * @information: the struct being formed
 * @string: string provided to alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *information, char *string)
{
	char *b, z;
	int result;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	z = *b;
	*p = 0;
	result = (delete_node_at_index(&(information->alias)), get_node_index
		(information->alias, node_starts_with(information->alias,
			string, -1)));
	*b = z;
	return (result);
}

/**
 * set_alias - a function that sets an alias string
 * @information: the struct being formed
 * @string: a string alias to be set
 * Return: Always 0 on success or 1 on error
 */
int set_alias(info_t *information, char *string)
{
	char *b;

	b = _strchr(string, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(information, string));

	unset_alias(information, string);
	return (add_node_end(&(information->alias), string, 0) == NULL);
}

/**
 * print_alias - a function prints string alias
 * @node: node of the alias to be set
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *b = NULL, *e = NULL;

	if (node)
	{
		b = _strchr(node->string, '=');
		for (e = node->string; a <= b; e++)
			_putchar(*e);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - a fucntion that imitates the alias builtin handles man alias
 * @information: a structure
 * Return: Always 0
 */
int _myalias(info_t *information)
{
	int x = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (information->argc == 1)
	{
		node = information->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; information->argv[x]; x++)
	{
		b = _strchr(information->argv[x], '=');
		if (b)
			set_alias(information, information->argv[x]);
		else
			print_alias(node_starts_with(information->alias,
						information->argv[i], '='));
	}

	return (0);
}
