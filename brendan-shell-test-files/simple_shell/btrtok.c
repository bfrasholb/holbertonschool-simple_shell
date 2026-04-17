#include "main.h"

int btrtok(char **args, char *line)
{
	int i = 0;
	char *l = line, quotes;

	while (*l)
{
	while (*l == ' ' || *l == '\t' || *l == '\n')
		l++;
	if (*l == '\0')
		break;

	if (*l == '\"' || *l == '\'')
	{
		quotes = *l;
		l++;
		args[i] = l;
		i++;
		while (*l && *l != quotes)
			l++;
	}
	else
	{
			args[i] = l;
			i++;
			while (*l && *l != ' ' && *l != '\t' && *l != '\n')
				l++;
	}
	if (*l)
	{
		*l = '\0';
		l++;
	}
}
	args[i] = NULL;
	return (i);
}