#include "test.h"

int main(void) {
	int i = 0;
	pid_t pid, my_pid;
	char *argv[] = {"/bin/ls", NULL};

	while (i < 5)
	{
		pid = fork();
		if (pid == 0)
		{
			my_pid = getpid();
			printf("CHILD PID = %u\n", my_pid);
			execve(argv[0], argv, NULL);
		}
		else
		{
			wait(NULL);
			my_pid = getpid();
			printf("PARENT PID = %u\n", my_pid);
		}
		i++;
 	}
	return (0);
}
