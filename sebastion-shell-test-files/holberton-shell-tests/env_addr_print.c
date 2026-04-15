#include "test.h"

extern char **environ;

int main(int argc, char **argv, char **env)
{
	printf("environ = %p\n", environ);
	printf("env = %p\n", env);
	return (0);
}
