#include "main.h"

char *get_path(char *cmd)
{
	char *path;
	char *copy;
	char *dir;
	char full[1024];

	path = getenv("PATH");
	if (!path)
		return (NULL);

	copy = strdup(path);
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
		snprintf(full, sizeof(full), "%s/%s", dir, cmd);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (strdup(full));
		}
		dir = strtok(NULL, ":");
	}

	free(copy);
	return (NULL);
}