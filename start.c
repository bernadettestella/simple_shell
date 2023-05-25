#include "main.h"

size_t _lenstr(const char *st);

/**
 * handles_exit - handles the exit option from shell
 * @arr: array of commadns to be executed
 * @line: where user will write
 * @newline: user input with new line option
 * @command_count: number of commands keyed in by user
 * Return: o on success
 */

int handles_exit(char **line, char *newline, char **arr, int command_count)
{
	int number, z = 0;
	char *command_num;
	char count_str[20];

	if (arr[1] == NULL)
	{
		all_free(line, newline, arr);
		exit(2);
	}

	else
	{
		number = atoi(arr[1]);
		if (number == -1)
		{
			command_num = prints_integer(command_count);
			write(STDERR_FILENO, arr[0], _lenstr(arr[0]));
			snprintf(count_str, sizeof(count_str), "%d",
					command_count);
			write(STDERR_FILENO, &command_count,
					_lenstr(command_num));
			write(STDERR_FILENO, ": exit: wrong number: ", 22);
			while (arr[1][z] != '\0')
				z++;
			write(STDOUT_FILENO, &(arr[1]), z);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		all_free(line, newline, arr);
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
		if (chdir(gets_env("HOME", env)) == -1)
		{
			perror(arr[0]);
			write(STDERR_FILENO, "cannot cd to home\n", 18);
		}
	}

	else
	{
		getcwd(cwd, 1024);
		while (cwd[x] != '\0')
			x++;
		cwd[x++] = '/';
		cwd[x] = '\0';
		new_directory = str_conc(cwd, arr[1]);
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
		write(STDOUT_FILENO, env[x], leng);
		write(STDOUT_FILENO, "\n", 1);
		x++;
	}
	return (0);
}

/**
 * builtin_checker - fucntion to check whether builtins exist in shell
 * @arr: an array of strings
 * @env: the env variable to be passed
 * @line: the user input place
 * @newline: input without newline character put after statements
 * @cmd_number: the number of commands keyed in the shell by user
 * Return: 0 if command builtin is present and 1 if absent
 */

int builtin_checker(char **arr, char **env, char *line, char *newline,
		int cmd_number)
{
	if (arr == NULL || *arr == NULL)
		return (1);
	if (env == NULL || *env == NULL)
		return (1);
	if (str_cmp((arr[0]), "exit") == 0)
		return (handles_exit(&line, newline, arr, cmd_number));
	else if (str_cmp((arr[0]), "cd") == 0)
		return (handles_cd(arr, env));
	else if (str_cmp((arr[0]), "env") == 0)
	return (handles_env(env));
	else
	return (1);
}
