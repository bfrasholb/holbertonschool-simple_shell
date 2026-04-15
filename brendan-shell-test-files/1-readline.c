#include "main.h"

/**
 * readline- reads from stdin and stores it
 * Return: chars read on success, nothing on failure
 */

int main(void)
{
	char *buffer;
	size_t len = 0;
	ssize_t read;

	printf("$ ");
	fflush(stdout);

	read = getline(&buffer, &len, stdin);

	if (read != -1)
		printf("%s", buffer);
	else
		printf("Error reading input\n");

	free (buffer);
	return (0);
}
