#include "test.h"

int in_path(char *file)
{
	char *path = strdup(getenv("PATH"));
	char *token;
	char *fullpath;
	struct stat st;
	

	token = strtok(path, ":");
	while (token != NULL)
	{
		fullpath = malloc(strlen(token) + strlen(file) + 2);
		strcpy(fullpath, token);
		fullpath[strlen(token)] = '/';
		fullpath[strlen(token) + 1] = '\0';
		strcat(fullpath, file);

		if (stat(fullpath, &st) == 0)
		{
			free(path);
			free(fullpath);
			return (0);
		}
		else
		{
			free(fullpath);
		}
		token = strtok(NULL, ":");
	}
	free(path);
	return (1);
}

/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	unsigned int i;
	struct stat st;

	if (ac < 2)
	{
	printf("Usage: %s path_to_file ...\n", av[0]);
	return (1);
	}
	i = 1;
	while (av[i])
	{
	printf("%s:", av[i]);
	if (stat(av[i], &st) == 0 || in_path(av[i]) == 0)
	{
	printf(" FOUND\n");
	}
	else
	{
	printf(" NOT FOUND\n");
	}
	i++;
	}
	return (0);
}
