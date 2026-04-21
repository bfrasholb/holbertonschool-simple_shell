#include "shell.h"

/**
 * validate_command - check if a command is valid
 * @argv: program calling this function
 * @args: args provided including command
 * @arglen: number of args in args
 * Return: status code on fail or 0 on sucsess
 */
int validate_command(char **argv, char **args, int arglen)
{
	struct stat st;

	if (args[0][0] == '/' || (args[0][0] == '.'))
	{
		if (stat(args[0], &st) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, args[0]);
			free_string_array(args, arglen);
			return (127);
		}
	}
	else if (search_path(&args[0], 1) == 1)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], 1, args[0]);
		free_string_array(args, arglen);
		return (127);
	}
	return (0);
}
