#include "shell.h"

/**
 * main - printenv program
 *
 * @ac: Argument Count
 * @av: Argument Vector
 * @env: Environment parameter
 * Return: 0 (Success).
 */
int main(int ac, char **av, char **env)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
