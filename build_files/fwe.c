#include "shell.h"

/**
 * main - Fork + Wait + Execve example
 *
 * Return: 0 (Success).
 */
int main(void)
{
	pid_t process_id;
	pid_t child_process_id;
	int status;

	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	char *env_args[] = {"PATH=/bin", (char *)0};

	process_id = getpid();
	printf("Hi, I'm the parent process. My pid is %u\n", process_id);
	for (int i = 1; i <= 5; i++)
	{
		printf("I am process #%d\n", i);
		child_process_id = fork();
		if (child_process_id == -1)
		{
			perror("Error:");
			return (1);
		}

		if (child_process_id == 0)
		{
			if (execve(argv[0], argv, env_args) == -1)
				perror("Error:");
			sleep(3);
		}
		else
		{
			wait(&status);
			printf("(%u) %u, I am your father i.e. the parent process\n\n",
			process_id, child_process_id);
		}
	}
	return (0);
}
