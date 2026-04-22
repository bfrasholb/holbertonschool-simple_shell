#include "shell.h"

/**
 * print_env- print environment variables
 * @env: pointer to environment var
 */

void print_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * array_length- measures the array length
 * @arr: array to measure
 * Return: length of array
 */

int array_length(char **arr)
{
	int len = 0;

	while (arr[len])
	{
		len++;
	}
	return (len);
}

/**
 * prompt- prints the prompt
 * @prompt: the prompt string
 */

void prompt(char *prompt)
{
	if (isatty(STDIN_FILENO))
	{
		printf("%s", prompt);
		fflush(stdout);
	}
}

/**
 * shell_read - print prompt and read next line
 * @line: pointer to character array for getline
 * @len: length of string line points to
 * Return: number of characters read
 */
int shell_read(char **line, size_t *len)
{
	ssize_t read;

	prompt("shell$ ");
	read = getline(line, len, stdin);
	if (read > 1)
		if ((*line)[read - 1] == '\n')
			(*line)[read - 1] = '\0';
	return (read);
}


