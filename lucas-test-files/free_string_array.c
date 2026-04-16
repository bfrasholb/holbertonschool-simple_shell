#include "shell.h"

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
