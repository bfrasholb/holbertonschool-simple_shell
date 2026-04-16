#include "shell.h"

/**
 * main- host process
 * Return: 0
 */

int main(void)
{
	char **env = environ;
	char *line = NULL;
	int RUN = 0;

	while (RUN == 0)
	{
		RUN = shell(env, line);
	}
	free(line);
	return (0);
}

/**
 * shell- write a prompt, and accept command line input
 * @env: pointer to environment var
 * @line: buffer to save command
 * Return: 0 to continue prompt, 1 to exit shell
 */

int shell(char **env, char *line)
{
	char **args;
	ssize_t read;
	size_t len = 0;
	int arglen;
	struct stat st;
	pid_t fork_id;

	prompt("sybau");
	read = getline(&line, &len, stdin);
	if (read == 1)
		return (0);
	if (read == -1)
		return (1);
	if (line[read - 1] == '\n')
		line[read - 1] = '\0';
	args = str_to_arr(line);
	arglen = array_length(args);
	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		free_string_array(args, arglen);
		return (1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		print_env(env);
		return (0);
	}
	if (stat(args[0], &st) && search_path(&args[0], 1) == 1)
		return (!(printf("command not found: %s\n", args[0])));
	fork_id = fork();
	if (fork_id == 0 && execve(args[0], args, env) == -1)
	{
		perror("Error:");
		return (1);
	}
	else
		wait(NULL);
	free_string_array(args, arglen);
	return (0);
}
