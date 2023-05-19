#include "main.h"

/**
 * exec_command - a function to execute line of code in the simple shell
 * @arr: an array of string commands to be executed
 * @env: the environment variable to be passed
 * @argv: an arrayof command line argument strings
 * @line: the liner where user will input
 * @newline: the user input with newline character
 * @command_count: the number of user input commands
 * Return: 0 if success or -1 on failure
 */

int exec_command(char *arr, char **env, char **argv, char *line, char *newline,
		int command_count)
{
	pid_t my_pid;
	char *concat;
	int sign;
	struct stat status;

	if (arr == NULL || *arr == NULL || argv == NULL || *argv == NULL)
		return (-1);
	if (env == NULL || *env == NULL)
		return (-1);
	if (checks_builtin(arr, env, line, newline, command_count) == 0)
		return (0);
	my_pid = fork();
	if (my_pid == -1)
	{
		write(STDOUT_FILENO, "Forking error", 13);
		return (-1);
	}
	if (my_pid == 0)
	{
		if (arr[0][0] == '/')
		{
			if (stat(arr[0], &status) == -1)
				handles_error(argv, arr, command_count, line,
						newline);
			if (access(arr[0], X_OK) == -1)
				handles_error(argv, arr, command_count, line,
						newline);
			execve(arr[0], arr, NULL);
		}
		else
		{
			concat = handles_path(arr[0], env);
			if (concat == NULL)
				handles_error(argv, arr, command_count, line,
						newline);
			else
				execve(concat, arr, NULL);
		}
	}
	else
		wait(&signal);
	return (0);
}
