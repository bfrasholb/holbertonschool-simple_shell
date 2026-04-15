#include "main.h"

/**
 * main- prints the max ppid
 * Return: 0
 */

int main(void)
{
	system("cat /proc/sys/kernel/pid_max");
	return (0);
}
