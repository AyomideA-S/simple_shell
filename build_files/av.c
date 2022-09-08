#include <stdio.h>

/**
 * main - AV
 *
 * @ac: Argument Count
 * @av: Argument Vector
 * Return: 0 (Success)
 */
int main(int ac, char **av)
{
	while (*av != NULL)
	{
		printf("%s\n", *av);
		ac--;
		av++;
	}
	return (0);
}
