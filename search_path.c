#include "shell.h"

/**
 * search_path- print environment variables
 * @file: filename string
 * @overwrite: bool: overwrite filename with absolute path
 * Return: 1 if file not found, else 0
 */

int search_path(char **file, int overwrite)
{
	char *getpath = _getenv("PATH");
	char *path;
	char *token;
	char *fullpath;
	struct stat st;

	if (getpath != NULL)
		path = strdup(getpath);
	else
		return (1);

	token = strtok(path, ":");
	while (token != NULL)
	{
		fullpath = malloc(strlen(token) + strlen(*file) + 2);
		strcpy(fullpath, token);
		fullpath[strlen(token)] = '/';
		fullpath[strlen(token) + 1] = '\0';
		strcat(fullpath, *file);

		if (stat(fullpath, &st) == 0)
		{
			free(path);
			if (overwrite == 1)
			{
				free(*file);
				*file = fullpath;
			}
			else
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
