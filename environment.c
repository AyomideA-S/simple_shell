#include "shell.h"

/**
 * lookup - Function to compare two given keys.
 *
 * @key: Entry to search for in a dictionary.
 * @entry: Specific entry from a dictionary to be comparedto the provided key.
 * Return: 1 if key is found in the entry else -1.
 */
int lookup(const char *key, char *entry)
{
	unsigned int c;

	c = 0;
	while (key[c] != '\0')
	{
		if (key[c] == entry[c])
			c++;
		else
			return (-1);
	}
	return (c);
}

/**
 * _getenv - Function to get an environment variable.
 *
 * @name: Name of the specified variable.
 * Return: Value of the variable key provided else error message.
 */
char *_getenv(const char *name)
{
	unsigned int i, j;
	int outcome;
	char *value = malloc(255 * sizeof(char));

	i = 0;
	j = 0;
	while (environ[i] != NULL)
	{
		outcome = lookup(name, environ[i]);
		if (outcome != -1)
		{
			while (environ[i][++outcome] != '\0')
			{
				*value = environ[i][outcome];
				value++;
				j++;
			}
			while (j > 0)
			{
				value--;
				j--;
			}
			return (value);
		}
		i++;
	}
	free(value);
	return ("\0");
}

/**
 * print_path - Function that prints evey directory in the PATH variable.
 */
void print_path(void)
{
	unsigned int i;
	char *PATH = _getenv("PATH");

	i = 0;
	while (PATH[i] != '\0')
	{
		if (PATH[i] == ':')
			printf("\n");
		else
			printf("%c", PATH[i]);
		i++;
	}
}
