#include "shell.h"

/**
 * print_env - prints the current environment
 *
 * Return: void
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
