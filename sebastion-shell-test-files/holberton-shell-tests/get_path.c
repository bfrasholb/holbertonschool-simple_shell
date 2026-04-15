#include "test.h"

extern char **environ;

int main(void)
{
	char *path = strdup(getenv("PATH"));
	char *token;

	token = strtok(path, ":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}

	free(path);
	return (0);
}
