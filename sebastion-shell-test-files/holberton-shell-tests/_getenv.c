#include "test.h"

extern char **environ;

char *_getenv(char *name)
{
	char **env = environ;
	size_t len = strlen(name);

	while (env != NULL)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			return (*env + len + 1);
		}
		env++;
	}

	return (NULL);
}

int main(void)
{
	char *path;
	
	path = _getenv("PATH");

	printf("path = %s", path);

	return (0);
}
