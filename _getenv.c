#include "shell.h"

/**
 * _getenv - copy of the c getenv function
 * @name: name of env variable to get
 * Return: pointer to the env variable of name or NULL if not present
 */
char *_getenv(char *name)
{
	char **env = environ;
	size_t len = strlen(name);

	while (env != NULL && *env != NULL)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			return (*env + len + 1);
		}
		env++;
	}

	return (NULL);
}
