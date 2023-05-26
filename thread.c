#include "main.h"

/**
 * add_node - a function that adds a node to the start of the list
 * @str: str field of node
 * @head: address pointer
 * @numb: node index used by history
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int numb)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->numb = numb;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - a function that appends a node to the end of the list
 * @numb: the index of the node used in the history
 * @head: a pointer to the head node of a data structure.
 * @str: the string value stored in the node
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int numb)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - a func displays solely the str element of a
 * list_t linked list
 * @head: pointer to the first node of the linked list
 * Return: the size of the linked list
 */

size_t print_list_str(const list_t *head)
{
	size_t x = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - a function that removes the node located at
 * the specified index
 * @head: a pointer to the first node in the linked list.
 * @index: the index of node to be removed
 * Return: 1 on successful deletion of the node or 0 if the deletion
 * operation failed.
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (x == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list -a function that deallocate_list releases all nodes in a list.
 * @head_ptr: a pointer to the address of the head node in the list
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
