#include "shell.h"

extern char **environ;

int main(int argc, char **argv, char **env)
{
	char **args;
	char *line = NULL;
	ssize_t read;
	size_t len = 0;
	int RUN = 1;
	int i;
	int arglen;
	int cmpres;
	struct stat st;
	pid_t fork_id;

	while (RUN)
	{
		printf("#sebshell$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);

		if (read == 1)
			continue;
		if (read == -1)
		{
			free(line);
			return 0;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		
		args = str_to_arr(line);

		arglen = 0;
		while (args[arglen])
		{
			arglen++;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free_string_array(args, arglen);
			return 0;
		}
		if (strcmp(args[0], "env") == 0)
		{
			i = 0;
			while (env[i] != NULL)
			{
				printf("%s\n", env[i]);
				i++;
			}
			continue;
		}

		if (stat(args[0], &st))
		{
			if (search_path(&args[0], 1) == 1)
			{
				printf("command not found: %s\n", args[0]);
				continue;
			}
		}

		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve(args[0], args, env) == -1)
			{
				perror("Error:");
			}
			return (0);
		}
		else
		{
			wait(NULL);
		}
		free_string_array(args, arglen);
	}
	free(line);
	return (0);
}
