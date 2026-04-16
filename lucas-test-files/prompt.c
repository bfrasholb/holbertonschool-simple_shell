#include "shell.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	printf("prompt$ ");
	fflush(stdout);

	read = getline(&line, &len, stdin);

	if (read != -1)
	{
		printf("%s", line);
	}
	else
	{
		printf("Error reading input\n");
	}

	free(line);
	return 0;
}