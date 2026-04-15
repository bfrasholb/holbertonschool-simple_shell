#include "test.h"

void free_string_array(char **arr, int size)
{
	int i = 0;

	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char **strtoarr(char *string)
{
	int i;
	int count = 0;
	char **strarr;
	char *token;
	char *str = strdup(string);

	token = strtok(str, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	free(str);

	strarr = malloc((count + 1) * sizeof(*strarr));
	if (!strarr)
	{
		return (NULL);
	}

	count = 0;
	str = strdup(string);
	token = strtok(str, " ");
	while (token != NULL)
	{
		strarr[count] = strdup(token);
		if (!strarr[count])
		{
			free_string_array(strarr, count);
			free(str);
			return(NULL);
		}

		token = strtok(NULL, " ");
		count++;
	}
	free(str);
	strarr[count] = NULL;
	return (strarr);
}


int main (int argc, char *argv[], char *env[])
{
	char **args;
	ssize_t read;
	size_t len = 0;
	pid_t fork_id;
	int RUN = 1;
	int arglen;
	char *line = NULL;
	int cmpres;

	while (RUN)
	{
		printf("#cisfun$ ");
		fflush(stdout);
		read = getline(&line, &len, stdin);
		if (read == 1)
			continue;
		if (read == -1)
		{
			printf("EOF\n");
			free(line);
			return 0;
		}
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		
		args = strtoarr(line);

		arglen = 0;
		while (args[arglen])
		{
			arglen++;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free_string_array(args, arglen);
			printf("EXITING!!!\n");
			return 0;
		}

		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve(args[0], args, env) == -1)
			{
				perror("Error:");
			}
			return (0);
		}
		else
		{
			wait(NULL);
		}
		free_string_array(args, arglen);
	}
	free(line);
	return (0);
}
