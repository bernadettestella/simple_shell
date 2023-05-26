#include "main.h"

/**
 * input_buf - a function that utilize buffers
 * @len: var address
 * @information: a struct
 * @buf: buffer address
 * Return: the  bytes read
 */

ssize_t input_buf(info_t *information, char **buf, size_t *len)
{
	ssize_t i = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		i = getline(buf, &len_p, stdin);
#else
		i = _getline(information, buf, &len_p);
#endif
		if (i > 0)
		{
			if ((*buf)[i - 1] == '\n')
			{
				(*buf)[i - 1] = '\0';
				i--;
			}
			information->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(information, *buf,
					information->histcount++);
			{
				*len = i;
				information->cmd_buf = buf;
			}
		}
	}
	return (i);
}

/**
 * get_input - a func that retrieve a string without the line break character
 * @information: a struct
 * Return: bytes read
 */

ssize_t get_input(info_t *information)
{
	static char *buf;
	static size_t x, j, len;
	ssize_t r = 0;
	char **buf_p = &(information->arg), *b;

	_putchar(BUF_FLUSH);
	r = input_buf(information, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = x;
		b = buf + x;

		check_chain(information, buf, &j, x, len);
		while (j < len)
		{
			if (is_chain(information, buf, &j))
				break;
			j++;
		}

		x = j + 1;
		if (x >= len)
		{
			x = len = 0;
			information->cmd_buf_type = CMD_NORM;
		}

		*buf_p = b;
		return (_strlen(b));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - a function that reads a buffer
 * @j: size
 * @information: a struct
 * @buf: buffer
 * Return: r
 */

ssize_t read_buf(info_t *information, char *buf, size_t *j)
{
	ssize_t r = 0;

	if (*j)
		return (0);
	r = read(information->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*j = r;
	return (r);
}

/**
 * _getline - a function that retrieves the next line of input STDIN stream
 * @ptr: a pointer to the buffer
 * @information: a struct
 * @leng: the size of the preallocated buffer if its not null
 * Return: st
 */

int _getline(info_t *information, char **ptr, size_t *leng)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t l;
	ssize_t j = 0, st = 0;
	char *b = NULL, *new_b = NULL, *z;

	b = *ptr;
	if (b && leng)
		st = *leng;
	if (x == len)
		x = len = 0;

	j = read_buf(information, buf, &len);
	if (j == -1 || (j == 0 && len == 0))
		return (-1);

	z = _strchr(buf + x, '\n');
	l = z ? 1 + (unsigned int)(z - buf) : len;
	new_b = _realloc(b, st, st ? st + l : l + 1);
	if (!new_b)
		return (b ? free(b), -1 : -1);

	if (st)
		_strncat(new_b, buf + x, l - x);
	else
		_strncpy(new_b, buf + x, l - x + 1);

	st += l - x;
	x = l;
	b = new_b;

	if (leng)
		*leng = st;
	*ptr = b;
	return (st);
}

/**
 * sigintHandler - a function that prevents ctrl-C from functioning
 * @sig_num: the signal integer
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
