#include "shell.h"

/**
 * input - Collects a line of input from a user.
 *
 * @lineptr: Line buffer
 * @n: Size of the line
 * @stream: The FILE stream
 * Return: Line of input.
 */
ssize_t input(char **lineptr, size_t *n, FILE *stream)
{
	const size_t ALLOCSTEP = 16;
	size_t count = 0;
	int c;

	while (((c = (char)getc(stream)) != '\n' && EOF != c))
	{
		if (count >= *n)
		{
			char *tmp = realloc(*lineptr, *n + ALLOCSTEP + 1);

			if (tmp != NULL)
			{
				*lineptr = tmp;
				*n += ALLOCSTEP;
			}
			else
			{
				return (-1);
			}

			if (*n > SSIZE_MAX)
			{
				errno = ERANGE;
				return (-1);
			}
		}

	(*lineptr)[count++] = c;
	}
	(*lineptr)[count] = '\0';

	return ((ssize_t) (count));
}

/**
 * split - Function that tokenizes input into an array
 *
 * @str: String to be tokenized.
 * @delim: The delimiter.
 * Return: Argument vector.
 */
char **split(char *str, const char *delim)
{
	char **av;
	int count = -1, x = 0, y = 0;

	av = (char **)malloc(sizeof(char *));
	av[x] = (char *)malloc(sizeof(char));
	while (str[++count] != '\0')
	{
		av[x] = (char *)realloc(av[x], sizeof(char) * (y + 1));
		if (str[count] == *delim)
		{
			av[x][y] = '\0';
			x++;
			y = 0;
			av = (char **)realloc(av, (x + 1) * sizeof(char *));
			av[x] = (char *)malloc(sizeof(char));
		}
		else
		{
			av[x][y] = str[count];
			y++;
		}
	}
	av[++x] = NULL;
	av[--x][y] = '\0';

	return (av);
}

/**
 * prompt - Continually prompts the user for commands and executes them
 *
 * @command: String of commands provided by user
 * @size: Size of the commmand string
 * @env_args: Environment arguments
 * Return: 0 (Exit code).
 */
int prompt(char *command, size_t size, char *env_args[])
{
	pid_t subprocess_id;
	int status;

	char **argv;
	ssize_t bytes_read;
	char delim = ' ';

	while ((bytes_read = input(&command, &size, stdin)))
	{
		if (bytes_read == -1)
			puts("ERROR!");

		argv = split(command, &delim);

		if (strcmp("exit", argv[0]) == 0)
			return (0);

		subprocess_id = fork();
		if (subprocess_id == -1)
		{
			perror("Error:");
			return (1);
		}

		if (subprocess_id == 0)
		{
			if (execve(argv[0], argv, env_args) == -1)
				perror("Error:");
			sleep(1);
		}
		else
		{
			wait(&status);
		}
		_putchar('$');
		_putchar(' ');
	}
	free(argv);
	argv = NULL;
	return (0);
}

/**
 * main - A super simple shell
 *
 * Return: 0 (success).
 */
int main(void)
{
	char *env_args[] = {"PATH=/bin", (char *)0};
	char *command = NULL;
	size_t size = 0;

	command = (char *)malloc(size);

	_putchar('$');
	_putchar(' ');
	prompt(command, size, env_args);

	free(command);
	command = NULL;
	return (0);
}
