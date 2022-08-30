#include "shell.h"

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", ".", NULL};
	char *env_args[] = {"PATH=/bin", (char *)0};

	printf("Before execve\n");

	if (execve(argv[0], argv, env_args) == -1)
		perror("Error:");

	printf("After execve\n");
	return (0);
}
