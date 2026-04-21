#include "shell.h"
#include <sys/stat.h>

static int line_count = 1;

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	char **args;
	char *line = NULL;
	char *cmd;
	ssize_t read;
	size_t len = 0;
	int RUN = 1;
	int i;
	int arglen;
	struct stat st;
	pid_t fork_id;
	int last_status = 0;

	while (RUN)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#lukeshell$ ");
			fflush(stdout);
		}
		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			free(line);
			return last_status;
		}

		if (read == 1)
		{
			line_count++;
			continue;

		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = str_to_arr(line);

		if (!args || !args[0])
		{
			if (args)
				free(args);

				line_count++;
			continue;
		}

		if (!args[0])
			continue;

		arglen = 0;
		while (args[arglen])
		{
			arglen++;
		}

		cmd = strdup(args[0]);

		if (strcmp(args[0], "exit") == 0)
		{
			free(cmd);
			free(line);
			free_string_array(args, arglen);
			return last_status;
		}
		if (strcmp(args[0], "env") == 0)
		{
			i = 0;
			while (env[i] != NULL)
			{
				printf("%s\n", env[i]);
				i++;
			}
			free(cmd);
			free_string_array(args, arglen);
			last_status = 0;
			line_count++;
			continue;
		}

		if (stat(args[0], &st) == -1)
		{
			if (search_path(&args[0], 1) == 1)
			{
				fprintf(stderr, "%s: %d: %s: not found\n",argv[0] , line_count , cmd);

				free(cmd);
				free_string_array(args , arglen);
				last_status = 127;
				line_count++;
				continue;
			}

			free(cmd);
			cmd = strdup(args[0]);
		}

		fork_id = fork();
		if (fork_id == 0) 
		{
			if (execve(args[0], args, env) == -1)
				_exit(127);
		}
		else
		{
			int status;
			waitpid(fork_id, &status, 0);

			if (WIFEXITED(status))              
				last_status = WEXITSTATUS(status);  
		}
		
		free(cmd);
		free_string_array(args, arglen);
		line_count++;
	}
	free(line);
	return (last_status);
}
