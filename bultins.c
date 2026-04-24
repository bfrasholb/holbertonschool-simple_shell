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
		char *err = "Illegal number";

		while (digit)
		{
			if (!_isdigit(digit) || digit == '-')
			{
				fprintf(stderr, "%s: %d: %s: %s: %s\n", argv[0], 1, args[0], err, args[1]);
				free_string_array(args, arglen);
				return (2);
			}
			i++;
			digit = args[1][i];
		}
		l_stat = _atoi(args[1]);
	}
	free_string_array(args, arglen);
	exit(l_stat);
}
