#include "main.h"

int main(void)
{
	char *line = NULL, *args[1024];
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("simpleshell >$ ");
		fflush(stdout);
		read = getline(&line, &len, stdin);

		if (read == -1)
			break;
		if (strcmp(line, "exit\n") == 0)
			break;
		else
		{
			btrtok(args, line);
			execute(args);
		}
	}
	free(line);
	return (0);
}