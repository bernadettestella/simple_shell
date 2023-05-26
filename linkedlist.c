#include "main.h"

/**
 * list_len - a function that computes the size of a linked list
 * @head: a pointer to the first node of the linked list
 * Return: the length of linked list
 */

size_t list_len(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * list_to_strings - a function that generates an array of
 * strings from the list->str data type
 * @head: a pointer to first node in the linked list
 * Return: An array of strings containing the list->str data type
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t x = list_len(head), k;
	char **strs;
	char *str;

	if (!head || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < x; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list - The function outputs all the elements stored in a
 * linked list of type list_t
 * @head: a pointer to first node in the linked list
 * Return: the number of nodes in the linked list
 */

size_t print_list(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - a function that returns a pointer to the node in
 * the linked list
 * @ch: the character that follows the prefix
 * @node: pointer to the linked list head
 * @prefix: string to match in linked list
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char ch)
{
	char *b = NULL;

	while (node)
	{
		b = starts_with(node->str, prefix);
		if (b && ((ch == -1) || (*b == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - a function that retrieves the position
 * of a node in the list
 * @head: a pointer to the head of the list
 * @node: a pointer to the node whose position is to be retrieved
 * Return: The index of the node in the list
 * or -1 if the node is not found
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
