#include "shell.h"

/**
 * main - printenv
 *
 * @ac: Argument Count
 * @av: Argument Vector
 * @env: Environment parameter
 * Return: 0 (Success).
 */
int main(int ac, char **av, char **env)
{
	printf("Address of env: %x\n", **env);
	printf("Address of environ: %x\n", **environ);

	return (0);
}
