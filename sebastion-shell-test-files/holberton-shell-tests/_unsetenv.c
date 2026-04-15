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

int _unsetenv(const char *name)
{
	char **new_environ;
	char *new_var;
	size_t name_len;
	int i, n, x;

	if (!name || name[0] == '\0' || strchr(name, '=') != NULL)
	        return -1;

	name_len = strlen(name);

	i = 0;
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			while (environ[n] != NULL)
			{
				n++;
			}
			new_environ = malloc(n * sizeof(*new_environ));
			if (!new_environ)
			{
				free(new_var);
				return (-1);
			}
			n = 0;
			x = 0;
			while (environ[n] != NULL)
			{
				if (x == i)
				{
					x++;
				    	continue;
				}
				new_environ[n] = environ[x];
				n++;
				x++;
			}
			new_environ[n] = NULL;
			environ = new_environ;
		}
		i++;
	}
	return 0;
}

int main(void)
{
	printf("\nENV BEFORE\n\n");
	print_env();

	printf("\nUNSET EDITOR\n\n");
	_unsetenv("EDITOR");

	print_env();
}
