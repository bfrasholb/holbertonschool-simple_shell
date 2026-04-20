#include "shell.h"

/**
 * str_to_arr- breaks a string down into component strings separated by ' \t\n'
 * @string: command string
 * Return: pointer to the first element of the args array
 */

char **str_to_arr(char *string)
{
	int count = 0;
	char **strarr;
	char *token;
	char *str = strdup(string);
	char *savepnt = NULL;

	token = cmd_tok(str, &savepnt);
	while (token != NULL)
	{
		count++;
		token = cmd_tok(str, &savepnt);
	}
	free(str);

	strarr = malloc((count + 1) * sizeof(*strarr));
	if (!strarr)
	{
		return (NULL);
	}

	count = 0;
	str = strdup(string);
	token = cmd_tok(str, &savepnt);
	while (token != NULL)
	{
		strarr[count] = strdup(token);
		if (!strarr[count])
		{
			free_string_array(strarr, count);
			free(str);
			return (NULL);
		}

		token = cmd_tok(str, &savepnt);
		count++;
	}
	free(str);
	strarr[count] = NULL;
	return (strarr);
}
