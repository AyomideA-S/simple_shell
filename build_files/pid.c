#include "shell.h"

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("Process ID: %u\n", my_pid);
	printf("Parent process ID: %u\n", getppid());
	return (0);
}
