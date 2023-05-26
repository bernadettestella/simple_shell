#include "main.h"

/**
 * is_chain -  checks whether the current character in the
 *	given buffer is a delimiter for a chain
 *
 * @information: a struct containing the required parameters for the function.
 * @buf: a character buffer to search for the delimiter.
 * @p: a pointer to the current position in the buffer.
 *
 * Return: 1if the current character is a delimiter for a chain, else 0
 */
int is_chain(info_t *information, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain -  verifies whether we should continue linking
 *	based on the previous status
 *
 * @information: a struct containing the parameters.
 * @buf: a character buffer.
 * @p: a pointer to the current position in the buffer.
 * @i: the starting position in the buffer.
 * @len: the length of the buffer.
 *
 * Returns: has no return value
 */

void check_chain(info_t *information, char *buf, size_t *p, size_t i, size_t
		len)
{
	size_t j = *p;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - substitutes an alias in the tokenized string
 *	with its corresponding value
 *
 *  @information: a struct containing  parameters for alias substitution
 *
 * Return:returns 1 if alias is substituded successfully else 0
 */

int replace_alias(info_t *information)
{
	int x;
	list_t *node;
	char *p;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(information->alias,
				information->argv[0], '=');
		if (!node)
			return (0);
		free(information->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - substitutes variables in the tokenized string
 *	with their corresponding values
 *
 * @information:  the parameter struct that contains information about the
 *			variables and their values.
 *
 * Return: returns 1 if the variables are successfully substituted else 0
 */
int replace_vars(info_t *information)
{
	int x = 0;
	list_t *node;

	for (x = 0; information->argv[x]; x++)
	{
		if (information->argv[x][0] != '$' || !information->argv[x][1])
			continue;

		if (!_strcmp(information->argv[x], "$?"))
		{
			replace_string(&(information->argv[x]),
				_strdup(convert_number(information->status,
						10, 0)));
			continue;
		}
		if (!_strcmp(information->argv[x], "$$"))
		{
			replace_string(&(information->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(information->env, &information->argv[x]
				[1], '=');
		if (node)
		{
			replace_string(&(information->argv[x]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&information->argv[x], _strdup(""));

	}
	return (0);
}

/**
 * replace_string -substitutes a string with a new one.
 *
 * @old: a pointer to the old string that needs to be replaced
 * @new: a pointer to the new string that will replace the old one
 *
 * Return: 1 if the replacement was successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
