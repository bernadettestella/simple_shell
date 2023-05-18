#include "main.h"

/**
 * handles_exit - handles the exit option from shell
 * @arr: array of commadns to be executed
 * @line: where user will write
 * @newline: user input with new line option
 * @command_count: number of commands keyed in by user
 * Return: o on success
 */

int handles_exit(char *line, char *newline, char **arr, int command_count)
{
	int number, z = 0;
	char *command_num;

	if (arr[1] == NULL)
	{
		free_all(line, newline, arr);
		exit(2);
	}

	else
	{
		number = _atoi(array[1]);
		if (number == -1)
		{
			command_num = print_int(command_count);
			write(STDERR_FILENO, arr[0], 7);
			write(STDERR_FILENO, command_count,
					_strlen(command_num));
			write(STDERR_FILENO, ": exit: wrong number: ", 22);
			while (arr[1][z] != '\0')
				z++;
			write(STDOUT_FILENO, arr[1], z);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		free_all(line, arr, newline);
		_exit(number);
	}
}

/**
 * handles_cd - function that enables changind of directory
 * @arr: array of commands to be executed
 * @env: the environment being passed
 * Return: 0 if success
 */

int handles_cd(char  **arr, char **env)
{
	int x = 0;
	char cwd[1024];
	char *new_directory;

	if (arr[1] == NULL)
	{
		if (chdir(_getenv("HOME", env)) == -1)
		{
			perror(arr[0]);
			write(STERR_FILENO, "cannot cd to home\n", 18);
		}
	}

	else
	{
		getcwd(cwd, 1024);
		while (cwd[x] != '\0')
			x++;
		cwd[x++] = '/';
		cwd[x] = '\0';
		new_directory = _strconcat(cwd, arr[1]);
		if (new_directory == NULL)
			return (0);
		if (chdir(new_directory) == -1)
		{
			perror(arr[0]);
			write(STDERR_FILENO, "cant cd into directory\n", 23);
		}
		free(new_directory);
	}
	return (0);
}

/**
 * handles_env - function that handles the environment
 * @env: the environment variable to be passed
 * Return: 0 if success
 */

int handles_env(char **env)
{
	int x = 0, leng = 0;

	while (env[x] != NULL)
	{
		leng = _strlen(env[x]);
		write(STDOUT_FILEN0, env[x], leng);
		write(STDOUT_FILENO, "\n", 1);
		x++;
	}
	return (0);
}

/**
 * builtin_checker - func to check if command exist in shell
 * @arr: array of strings to be executed
 * @env: the environment variable to be passed
 * @line: the user input
 * @newline: newline
 * @cmd_number: number of commands keyed in by the user
 * Return: 0 if command exist 1 if it doesnt exit
 */

int builtin_checker(char **arr, char **env, char *line, char *newline,
		int cmd_number)
{
	if (arr == NULL || *ar == NULL)
		return (1);
	if (env == NULL || *env == NULL)
		return (1);
	if (_strcmp((arr[0], "exit") == 0)
		return (handles_exit(arr, newline, line, cmd_number));
	else if (_strcmp((arr[0]), "cd") == 0)
		return (handles_cd(arr, env));
	else if (_strcmp((ar[0], "env") == 0)
		return (handles_env(env));
	else
		return (1);
}
