#include "shell.h"

/**
 * shell_exit - builting shell function for exiting
 * @argv: array with name of program
 * @args: array of args passed to exit
 * @arglen: lengths of args
 * @l_stat: last status code
 * Return: fail code on fail
 */
int shell_exit(char **argv, char **args, int arglen, int l_stat)
{
	if (args[1] != NULL)
	{
		int i = 0;
		char digit = args[1][i];
		char *err_msg = "numeric argument required";

		while (digit)
		{
			if (!isdigit(digit))
			{
				fprintf(stderr, "%s: %s: %s: %s\n", argv[0], args[0], args[1], err_msg);
				free_string_array(args, arglen);
				return (2);
			}
			i++;
			digit = args[1][i];
		}
		l_stat = atoi(args[1]);
	}
	free_string_array(args, arglen);
	exit(l_stat);
}
