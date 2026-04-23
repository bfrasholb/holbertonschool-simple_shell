#include "shell.h"

/**
 * main - host process
 * @argc: number of command line args
 * @argv: array of command line args
 * @env: array of enviroment variables
 * Return: 0
 */
int main(int argc, char **argv, char **env)
{
	int l_stat = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int arglen;

	(void)argc;
	while ((read = shell_read(&line, &len)))
	{
		signal(SIGINT, ignore);
		if (read == 1)
		{
			free(line);
			len = 0;
			continue;
		}
		args = str_to_arr(line);
		arglen = array_length(args);
		free(line);
		len = 0;

		if (args[0] == NULL)
			free_string_array(args, arglen);
		else
			l_stat = run_command(argv, args, arglen, env, l_stat);
	}
	if (read == -1)
		free(line);
	return (l_stat);
}

/**
 * run_command - run a command
 * @argv: array of command line args
 * @args: array args to pass to command
 * @arglen: length of args array
 * @env: enviroment variables
 * @l_stat: last exit status
 * Return: 0 to continue to next prompt, 1 to exit shell
 */

int run_command(char **argv, char **args, int arglen, char **env, int l_stat)
{
	int status;
	int cmd_val;
	pid_t fork_id;

	if (strcmp(args[0], "exit") == 0)
		return (shell_exit(argv, args, arglen, l_stat));
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
	exit(l_stat);
}
