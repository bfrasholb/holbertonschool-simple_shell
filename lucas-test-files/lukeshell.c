#include "shell.h"
#include <sys/stat.h>

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
	int last_status = 0;

	while (RUN)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("#lukeshell$ ");
			fflush(stdout);
		}
		read = getline(&line, &len, stdin);

		if (read == 1)
			continue;
		if (read == -1)
		{
			free(line);
			return last_status;
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
			free_string_array(args, arglen);
			last_status = 0;
			continue;
		}

		if (stat(args[0], &st))
		{
			if (search_path(&args[0], 1) == 1)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				free_string_array(args , arglen);
				last_status = 127;
				continue;
			}
		}

		fork_id = fork();
		if (fork_id == 0) 
		{
			if (execve(args[0], args, env) == -1)
			{
				perror("./hsh");
				_exit(127);
			}
		}
		else
		{
			int status;
			waitpid(fork_id, &status, 0);

			if (WIFEXITED(status))              
				last_status = WEXITSTATUS(status);  
		}                                       
		free_string_array(args, arglen);
	}
	free(line);
	return (last_status);
}
