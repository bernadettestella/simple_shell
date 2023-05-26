#include "main.h"

/**
 * hsh - the primary loop of the shell
 *
 * @information:  a struct containing the input parameters
 *	and return values of the function.
 * @argv: an array of arguments passed to the function from main()
 *
 * Return: 0 if the function executes successfully,
 *	1 if an error occurs, or an error code
 */
int hsh(info_t *information, char **argv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(information);
		if (interactive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(information);
		if (r != -1)
		{
			set_info(information, argv);
			builtin_ret = find_builtin(information);
			if (builtin_ret == -1)
				find_cmd(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_info(information, 0);
	}
	write_history(information);
	free_info(information, 1);
	if (!interactive(information) && information->status)
		exit(information->status);
	if (builtin_ret == -2)
	{
		if (information->err_num == -1)
			exit(information->status);
		exit(information->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - searches the builtin command
 *
 * @information: a struct containing input parameters and return values
 *
 * Return: 1 if the built-in command is not found.
 *	0 if the built-in command is executed successfully.
 *	1 if the built-in command is found but not executed successfully.
 *	-2 if the built-in command signals exit()
 */
int find_builtin(info_t *information)
{
	int x, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(information->argv[0], builtintbl[x].type) == 0)
		{
			information->line_count++;
			built_in_ret = builtintbl[x].func(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - searches for a command in the directories listed in
 *	the PATH environment variable.
 *
 * @information: struct containing information about the command to be found,
 *	including the command name and the result of the search
 *
 * Return: has no return value
 */

void find_cmd(info_t *information)
{
	char *path = NULL;
	int x, b;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (x = 0, b = 0; information->arg[x]; x++)
		if (!is_delim(information->arg[x], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(information, _getenv(information, "PATH="),
			information->argv[0]);
	if (path)
	{
		information->path = path;
		fork_cmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=")
			|| information->argv[0][0] == '/') &&
				is_cmd(information, information->argv[0]))
			fork_cmd(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_error(information, "not found\n");
		}
	}
}

/**
 * fork_cmd - creates a child process to execute a command using exec function
 *
 * @information: a struct that contains input parameters and
 *	return values for the function
 *
 * Return: has no return value
 */
void fork_cmd(info_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv,
					get_environ(information)) == -1)
		{
			free_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}
