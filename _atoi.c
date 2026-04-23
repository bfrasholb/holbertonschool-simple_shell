#include "shell.h"

/**
 * _atoi - convert a string to an integer
 * @s: string to convert
 * Return: the converted int
 */
int _atoi(char *s)
{
	int m = 0;
	int res = 0;
	int x = 0;

	while (s[x])
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			res = m % 2 ? (res * 10 - (s[x] - '0')) : (res * 10 + (s[x] - '0'));
		}
		else if (res != 0)
		{
			break;
		}
		else if (s[x] == '-')
		{
			m++;
		}
		x++;
	}
	return (res);
}
