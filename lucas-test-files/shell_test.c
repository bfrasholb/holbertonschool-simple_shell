#include "shell.h"

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	pid_t pid;
	int status;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		if (getline(&line, &len, stdin) == -1)
		{
			free(line);
			exit(0);
		}

		for (i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == '\n')
			{
				line[i] = '\0';
				break;
			}
		}

		pid = fork();

		if (pid == -1)
		{
			perror("Error");
			continue;
		}

		if (pid == 0)
		{
			char *argv[2];
			argv[0] = line;
			argv[1] = NULL;

			if (execve(line, argv, NULL) == -1)
			{
				perror("./hsh");
			}
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}