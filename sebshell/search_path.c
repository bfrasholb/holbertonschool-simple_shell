#include "shell.h"

int search_path(char **file, int overwrite)
{
	char *path = strdup(getenv("PATH"));
	char *token;
	char *fullpath;
	struct stat st;
	

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
