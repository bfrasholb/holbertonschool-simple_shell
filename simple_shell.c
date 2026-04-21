#include "shell.h"

/**
 * main- host process
 * @argc: number of command line args
 * @argv: array of command line args
 * @env: array of enviroment variables
 * Return: 0
 */

int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	int RUN = 0;
	int last_status;

	(void)argc;
	while (RUN != 1)
	{
		last_status = RUN;
		RUN = shell(argv, env, line);
	}
	return (last_status);
}

/**
 * shell- write a prompt, and accept command line input
 * @argv: array of command line args
 * @env: pointer to environment var
 * @line: buffer to save command
 * Return: 0 to continue prompt, 1 to exit shell
 */

int shell(char **argv, char **env, char *line)
{
	char **args;
	ssize_t read;
	size_t len = 0;
	int arglen;

	prompt("shell$ ");
	read = getline(&line, &len, stdin);
	if (read == 1)
	{
		free(line);
		return (0);
	}
	if (read == -1)
	{
		free(line);
		return (1);
	}

	if (line[read - 1] == '\n')
		line[read - 1] = '\0';
	args = str_to_arr(line);
	arglen = array_length(args);
	free(line);
	if (args[0] == NULL)
	{
		free_string_array(args, arglen);
		return (0);
	}
	return (run_command(argv, args, arglen, env));
}

/**
 * run_command - run a command
 * @argv: array of command line args
 * @args: array args to pass to command
 * @arglen: length of args array
 * @env: enviroment variables
 * Return: 0 to continue to next prompt, 1 to exit shell
 */

int run_command(char **argv, char **args, int arglen, char **env)
{
	int status;
	int cmd_val;
	pid_t fork_id;

	if (strcmp(args[0], "exit") == 0)
	{
		free_string_array(args, arglen);
		return (1);
	}
	if (strcmp(args[0], "env") == 0)
	{
		print_env(env);
		free_string_array(args, arglen);
		return (0);
	}
	cmd_val = validate_command(argv, args, arglen);
	if (cmd_val != 0)
		return (cmd_val);
	fork_id = fork();
	if (fork_id == 0 && execve(args[0], args, env) == -1)
	{
		perror("Error:");
		exit(1);
	}
	wait(&status);
	free_string_array(args, arglen);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
