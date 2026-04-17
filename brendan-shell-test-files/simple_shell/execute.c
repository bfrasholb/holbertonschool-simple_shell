#include "main.h"

void execute(char **argv)
{
	pid_t pid;
	char *path;

	if (!argv[0])
		return;

	path = NULL;

	if (argv[0][0] == '/')
		path = argv[0];
	else
	{
		path = get_path(argv[0]);
		if (!path)
		{
			fprintf(stderr, "Command not found: %s\n", argv[0]);
			return;
		}
	}

	pid = fork();
	if (pid == 0)
	{
		execv(path, argv);
		perror("error");
		exit(1);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}

	if (argv[0][0] != '/')
		free(path);
}