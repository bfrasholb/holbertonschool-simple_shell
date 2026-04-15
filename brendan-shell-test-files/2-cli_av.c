#include "main.h"

/**
 *
 */

char **split_words(char *str)
{
	char *copy;
	char *token;
	char **result;
	int count = 0, i = 0;

	if (!str)
		return (NULL);

	copy = strdup(str);
	if (!copy)
		return (NULL);

	token = strtok(copy, " \t\n");

	while (token)
	{
		count++;
		token = strtok(NULL, " \t\n");
	}

	free (copy);

	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);

	copy = strdup(str);
	token = strtok(copy, " \t\n");

	while (token)
	{
		result[i] = strdup(token);
		i++;
		token = strtok(NULL, " \t\n");
	}

	result[i] = NULL;

	free (copy);
	return (result);
}


/**
 * main- splits a string and returns an array of each word
 * Return:
 */

int main (void)
{
	char **words;
	int i = 0;

	words = split_words("Hello World! This is C Programming!");

	while (words[i])
	{
		printf("%s\n", words[i]);
		free (words[i++]);
	}
	free (words);

	return (0);
}
