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

	while (RUN)
	{
		if (isatty(STDIN_FILENO))
			printf("#lukeshell$ ");
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
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				free_string_array(args , arglen);
				continue;
			}
		}

		fork_id = fork();
		if (fork_id == 0) /** lucas */
		{
			if (execve(args[0], args, env) == -1)
			{
				perror("./hsh");
				/** ends the process inmediately  */
				_exit(127);
			}
		}
		else
		{
			int status;
			waitpid(fork_id, &status, 0); /** waits for the child and saves the data in status */

			if (WIFEXITED(status))              /** wait for child */
				cmpres = WEXITSTATUS(status);   /** if child exited normally */
		}                                       /** save its exit code*/
		free_string_array(args, arglen);
	}
	free(line);
	return (0);
}
