#include "main.h"

/**
  * is_cmd - checks whether a file is executable
  * @information: contains inforamtion about a file
  * @route: the path to the file
  *
  * Return: returns 1 if the file is executable otherwise 0
  */

int is_cmd(info_t *information, char *route)
{
	struct stat st;

	(void)information;

	if (!route || stat(route, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}

/**
  * dup_chars - duplicates characters within a given range
  * @last: the index of the last character to be duplicated
  * @first: the index of the first character to be duplicated
  * @str: a string containing the characters to be duplicated
  *
  * Return: returns a pointer to the new buffer
  */

char *dup_chars(char *str, int first, int last)
{
	static char buffer[1024];
	int x = 0, z = 0;

	for (z = 0, x = first; x < last; x++)
		if (str[x] != ':')
			buffer[z++] = str[x];

	buffer[z] = 0;

	return (buffer);
}

/**
  * find_path - finds the command in the PATH string
  * @command: the command to be located in the string
  * @information: contains additional info about the command
  * @str: contains the PATH enironment variable
  *
  * Return: returns the full path if command is present else returns NULL
  */

char *find_path(info_t *information, char *str, char *command)
{
	int x = 0, current_pos = 0;
	char *route;

	if (!str)
		return (NULL);

	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(information, command))
			return (command);
	}

	while (1)
	{
		if (!str[x] || str[x] == ':')
		{
			route = dup_chars(str, current_pos, x);
			if (!*route)
				_strcat(route, command);

			else
			{
				_strcat(route, "/");
				_strcat(route, command);
			}

			if (is_cmd(information, route))
				return (route);

			if (!str[x])
				break;

			current_pos = x;
		}
		x++;
	}
	return (NULL);
}
