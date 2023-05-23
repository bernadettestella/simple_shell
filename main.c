#include "main.h"
#define DELIMITERS " \t\0"

/**
  * main - the entry point of the function
  * @argc: the number of arguments passed
  * @argv: array of strings for the arguments passed
  * @env: the current environment
  *
  * Return: returns 0 when the useed presses ctrl_d
  */

int main(int argc, char **argv, char **env)
{
	char *line, *newline;
	size_t length = 0;
	ssize_t line_size;
	char **t_array;
	int cmd_number;

	void(argc), void(argv);
	while (1)
	{
		line = NULL;
		length = 0;
		cmd_number++;
		if (isatty(STDIN_FILENO) == 1)
			command_prompt();

		signal(SIGINT, handles_ctrlc);
		line_size = getline(&line, &length, stdin);
		if (line_size == EOF || line_size == -1)
			return (handles_ctrld(line));
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		newline = _reallocate(line);
		if (newline == NULL)
		{
			free(line);
			return (0);
		}
		t_array = give_token(newline);
		if (t_array == NULL)
		{
			free(line);
			free(newline);
			return (0);
		}
		exec_command(t_array, env, argv, line, newline, cmd_number);
		all_free(line, newline, t_array);
	}
}

/**
  * give_token - spilts the input into tokens and stores them into arrays
  * @line: the input to be split
  *
  * Return: returns the tokens given
  */

char **give_token(char *line)
{
	int x = 0;
	int count_t = 0;
	char **t_array;
	char *copy_t, *token;

	if (line == NULL)
		return (NULL);

	while (*(line + x) != '\0')
	{
		if (line[x] != ' ' && (line[x + 1] == ' ' || line[x + 1] ==
					'\0' || line[x + 1] == '\t'))
			count_t++;
		x++;
	}

	x = 0;
	t_array = malloc(sizeof(char *) * (count_t + 1));
	if (t_array == NULL)
		return (NULL);

	token = strtok(line, DELIMITERS);
	while (token != NULL)
	{
		copy_t = _upstrd(token);
		if (copy_t == NULL)
		{
			free(t_array);
			return (NULL);
		}

		*(t_array + x) = copy_t;
		token = strtok(NULL, DELIMITERS);
		x++;
	}

	*(t_array + x) = NULL;
	return (t_array);
}


