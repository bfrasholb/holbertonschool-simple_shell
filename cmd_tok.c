#include "shell.h"

/**
 * cmd_tok - split a string int tokens by space and quotes
 * @line: command line to split
 * @savepnt: last place split
 * Return: pointer to token or null if no more tokens
 */
char *cmd_tok(char *line, char **savepnt)
{
	char *tok = NULL, *l;
	char quotes;

	if (*savepnt)
		l = *savepnt;
	else
		l = line;
	for (; *l == ' ' || *l == '\t' || *l == '\n';)
		l++;
	if (*l == '\0')
	{
		*savepnt = NULL;
		return (NULL);
	}
	if (*l == '\"' || *l == '\'')
	{
		quotes = *l;
		l++;
		tok = l;
		while (*l && *l != quotes)
		{
			l++;
		}
	}
	else
	{
		tok = l;
		for (; *l && *l != ' ' && *l != '\t' && *l != '\n';)
			l++;
	}
	if (*l)
	{
		*l = '\0';
		*savepnt = l + 1;
	}
	else
		*savepnt = l;
	if (tok == NULL)
		*savepnt = NULL;
	return (tok);
}
