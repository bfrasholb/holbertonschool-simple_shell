#include "test.h"

extern char **environ;

void print_env(void)
{
	char **env = environ;
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

int _setenv(const char *name, const char *value, int overwrite)
{
	char **new_environ;
	char *new_var;
	size_t name_len;
	int i;

	if (!name || !value || name[0] == '\0' || strchr(name, '=') != NULL)
	        return -1;

	name_len = strlen(name);
	new_var = malloc(name_len + 1 + strlen(value) + 1);
	if (!new_var)
		return (-1);
	strcpy(new_var, name);
	new_var[name_len] = '=';
	new_var[name_len + 1] = '\0';
	strcat(new_var, value);

	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			if (overwrite == 0)
				return 0;
			else
			{
				environ[i] = new_var;
				return 0;
			}
		}
		i++;
	}

	new_environ = malloc((i + 2) * sizeof(*new_environ));
	if (!new_environ)
	{
		free(new_var);
		return (-1);
	}

	i = 0;
	while (environ[i] != NULL)
	{
	    new_environ[i] = environ[i];
	    i++;
	}
	new_environ[i] = new_var;
	new_environ[i + 1] = NULL;
	environ = new_environ;
	return 0;
}

int main(void)
{
	printf("\nENV BEFORE\n\n");
	print_env();

	printf("\nSET TIRED=TRUE\n\n");
	_setenv("TIRED", "TRUE", 1);

	print_env();

	printf("\nSET EDITOR=vim, 0\n\n");
	_setenv("EDITOR", "vim", 0);

	print_env();

	printf("\nSET EDITOR=vim, 1\n\n");
	_setenv("EDITOR", "vim", 1);

	print_env();
}
