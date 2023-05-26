#include "shell.h"

/**
 * get_history_file - a function that retrieves the history file
 * @information: a struct
 * Return: an allocated string containg history file
 */

char *get_history_file(info_t *information)
{
	char *buf, *direct;

	direct = _getenv(information, "HOME=");
	if (!direct)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direct) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direct);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - a function thatgenerates a new file
 * or appends to an existing file
 * @information: struct
 * Return: 1 on success, else -1
 */

int write_history(info_t *information)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!namefile)
		return (-1);

	fd = open(namefile, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(namefile);
	if (fd == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - a function that retrievess history from file
 * @information: a struct
 * Return: histcount on success, 0 otherwise
 */

int read_history(info_t *information)
{
	int x, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *namefile = get_history_file(information);

	if (!namefile)
		return (0);

	fd = open(namefile, O_RDONLY);
	free(namefile);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(information, buf + last, linecount++);
			last = x + 1;
		}
	if (last != x)
		build_history_list(information, buf + last, linecount++);
	free(buf);
	information->histcount = linecount;
	while (information->histcount-- >= HIST_MAX)
		delete_node_at_index(&(information->history), 0);
	renumber_history(information);
	return (information->histcount);
}

/**
 * build_history_list - a function that appends an entry to a linked list
 * @buf: buffer
 * @information: a structure
 * @linecount: linecount, histcount
 * Return: Always 0
 */

int build_history_list(info_t *information, char *buf, int linecount)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	add_node_end(&node, buf, linecount);

	if (!information->history)
		information->history = node;
	return (0);
}

/**
 * renumber_history - a function that reindexes linked list after
 * modifications are made
 * @information: a structure
 * Return: the new histcount
 */

int renumber_history(info_t *information)
{
	list_t *node = information->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (information->histcount = x);
}
