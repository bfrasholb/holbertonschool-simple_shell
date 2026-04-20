#include "shell.h"

int search_path(char **file, int overwrite)
{
	char *env_path;
	char *path;
	char *token;
	char *fullpath;
	struct stat st;
	
	env_path = _getenv("PATH");
	if (!env_path)
		return (1);

	path = strdup(env_path);

	if (!path)
		return (1);

	token = strtok(path, ":");
	while (token != NULL)
	{
		fullpath = malloc(strlen(token) + strlen(*file) + 2);
		if (!fullpath)
		{
			free(path);
			return (1);
		}
		strcpy(fullpath, token);
		strcat(fullpath, "/");
		strcat(fullpath, *file);

		if (stat(fullpath, &st) == 0)
		{
			free(path);
			if (overwrite == 1)
			{
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