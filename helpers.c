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
