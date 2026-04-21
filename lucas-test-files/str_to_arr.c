#include "shell.h"

char **str_to_arr(char *string)
{
	int count = 0;
	char **strarr;
	char *token;
	char *str;

	if (!string)
		return (NULL);
	
	str = strdup(string);
	if (!str)
		return (NULL);

	token = strtok(str, " \t");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	free(str);

	strarr = malloc((count + 1) * sizeof(*strarr));
	if (!strarr)
		return (NULL);

	count = 0;
	str = strdup(string);
	if (!str)
	{
		free(strarr);
		return (NULL);
	}

	token = strtok(str, " \t");
	while (token != NULL)
	{
		strarr[count] = strdup(token);
		if (!strarr[count])
		{
			free_string_array(strarr, count);
			free(str);
			return (NULL);
		}

		token = strtok(NULL, " \t");
		count++;
	}

	free(str);
	strarr[count] = NULL;
	return (strarr);
}