#include "shell.h"

/**
 * free_string_array- frees an array of strings
 * @arr: array to free
 * @size: size of array
 */

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
