#include "main.h"

/**
 * creates_linked - func that creates a linked list withsize of path variable
 * @trs: the path variable name
 * Return: a pointer to the created empty linked list
 */

linked_t *creates_linked(char *trs)
{
	int x = 0, nds = 1;
	linked_t *nd, *start, *temp, *finish;

	temp = malloc(sizeof(linked_t));
	if (temp == NULL)
		return (NULL);
	start = temp;

	finish = malloc(sizeof(linked_t));

	if (finish == NULL)
	{
		free(temp);
		return (NULL);
	}
	finish->next = NULL;
	while (trs[x] != '\0')
	{
		if (trs[x] == ':')
			nds++;
		x++;
	}

	while ((nds - 2) > 0)
	{
		nd = malloc(sizeof(linked_t));
		if (nd == NULL)
		{
			free(temp);
			free(finish);
			return (NULL);
		}
		temp->next = nd;
		temp = temp->next;
		nds--;
	}
	temp->next = finish;
	return (start);
}

/**
 * add_nodes_list - adds path var to empty node
 * @trs: path var name to be added
 * @lists: a pointer to the empty linked list
 * Return: pointer to the formed linked list
 */

linked_t *add_nodes_list(char *trs, linked_t *lists)
{
	linked_t *pointer, *start;
	char *direct;
	int x = 0, z = 0, stct = 0, dirlength = 0;

	if (trs == NULL || lists == NULL)
		return (NULL);
	start = lists;
	pointer = start;
	while (pointer != NULL)
	{
		if (trs[x] == ':' || trs[x] == '\0')
		{
			if (trs[x] != '\0')
				x++;
			direct = malloc(sizeof(char) * dirlength + 2);
			if (direct == NULL)
				return (NULL);
			while (trs[stct] != ':' && trs[stct] != '\0')
			{
				z++;
			}
			direct[z++] = '/';
			direct[z] = '\0';
			stct = x;
			z = 0;
			pointer->directory = direct;
			pointer = pointer->next;
		}

		else
		{
			dirlength++;
			x++;
		}
	}
	return (start);
}

/**
 * get_env - func that finds the environment variable
 * @title: the name of the environment var
 * @env: the environment variable to be passed
 * Return: a pointer to the environment variable
 */

char *get_env(const char *title, char **env)
{
	int x = 0, z = 0;

	if (title == NULL || env == NULL || *env == NULL)
		return (NULL);
	while (env[x] != NULL)
	{
		while (env[x][z] == title[z])
			z++;
		if  (env[x][z] == '=')
		{
			z++;
			return (&(env[x][z]));
		}
		x++;
		z = 0;
	}
	write(STDOUT_FILENO, "Does not exist in environment", 29);
	return (NULL);
}


/**
 * handles_path - func that goes through the path var and connects commands
 * @trs: the path variable to concatenate
 * @env: the environment var
 * Return: a pointer to the concatenated string
 */

char *handles_path(char *trs, char **env)
{
	char *path, *concat;
	linked_t *lists, *temp;
	struct stat st;

	if (trs == NULL || env == NULL || *env == NULL)
		return (NULL);
	path = get_env("PATH", env);
	if (path == NULL)
	{
		write(STDERR_FILENO, "Path not found", 14);
		_exit(0);
	}
	lists = creates_linked(path);
	if (lists == NULL)
	{
		write(STDERR_FILENO, "PATH has Issues", 15);
		_exit(0);
	}
	lists = add_nodes_list(path, lists);
	temp = lists;
	while (temp != NULL)
	{
		if (path[0] == ':')
			concat = str_conc("./", trs);
		else
			concat = str_conc(temp->directory, trs);
		if (concat == NULL)
			return (NULL);
		if (stat(concat, &st) == 0 && access(concat, X_OK) == 0)
		{
			freelist(lists);
			return (concat);
		}
		temp = temp->next;
		free(concat);
	}
	freelist(lists);
	return (NULL);
}
