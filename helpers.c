#include "shell.h"

void print_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int array_length(char **arr)
{
	int len = 0;

	while (arr[len])
	{
		len++;
	}
	return (len);
}

void prompt(char *prompt)
{
	if (isatty(STDIN_FILENO))
	{
		printf(prompt);
		fflush(stdout);
	}
}
