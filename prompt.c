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
 * _split - Function that tokenizes input into an array
 *
 * @str: String to be tokenized.
 * @delim: The delimiter.
 * @argp: Pointer to arg of type struct args.
 * Return: Argument vector.
 */
char **_split(char *str, const char *delim, struct args *argp)
{
	int ac;
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
	ac = ++x;
	av[x] = NULL;
	av[--x][--y] = '\0';
	argp->ac = ac;
	argp->av = av;
	return (av);
}

/**
 * main - A program to prompt user for input and print out the input
 * as well as tokenizing it.
 *
 * Return: void
 */
int main(void)
{
	struct args arg;
	struct args *argp = &arg;
	int ac;
	char **av;
	char *string = NULL;
	size_t size = 0;
	ssize_t bytes_read;
	char delim = ' ';

	_putchar('$');
	_putchar(' ');
	string = (char *)malloc(size);
	bytes_read = input(&string, &size, stdin);

	if (bytes_read == -1)
		puts("ERROR!");
	else
		printf("%s\n", string);

	av = _split(string, &delim, &arg);
	ac = argp->ac;

	while (ac)
	{
		--ac;
	}

	free(string);
	free(av);
	string = NULL;
	av = NULL;

	return (0);
}
