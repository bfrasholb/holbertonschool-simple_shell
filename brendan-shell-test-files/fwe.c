#include "main.h"

/**
 *
 */

int main(void)
{
	int i = 0;
	char *argv[] = {"ls", "-l", "/tmp", NULL};
	pid_t pid;

	while (i < 5)
	{
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit (EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execve("/bin/ls", argv, NULL);
			perror("execve");
			exit (EXIT_FAILURE);
		}
		else
			wait (NULL);
		i++;
	}
	return (0);
}
