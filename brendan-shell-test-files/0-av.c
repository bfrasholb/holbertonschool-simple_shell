#include "main.h"

/**
 * main- prints all the arguments
 * Return (0)
 */

int main(int ac, char **av)
{
	int i = 0;

	while (av[i])
	{
		printf("%s\n", av[i++]);
	}

	(void)ac;

	return (0);
}
