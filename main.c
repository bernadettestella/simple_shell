#include "main.h"

/**
  * main - the entry point of the code
  * @argc: the number of arguments passed
  * @argv: an array of the arguments passed
  *
  * Return: returns 0 if successful else 1
  */

int main(int argc, char **argv)
{
	info_t information[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		information->readfd = fd;
	}

	populate_env_list(information);

	read_history(information);

	hsh(information, argv);

	return (EXIT_SUCCESS);
}
