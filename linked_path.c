#include "shell.h"

/**
 * extract_path - Funtion to extract individual directories from PATH variable.
 *
 * @PATH: PATH value
 * @i: Pointer to where to start reading from.
 * @length: Length of the directory.
 * Return: An individual directory.
 */
char *extract_path(char *PATH, unsigned int *i, unsigned int *length)
{
	unsigned int j = 0;
	char *value = (char *)malloc(sizeof(char));

	while (PATH[*i] != '\0')
	{
		if (PATH[*i] == ':')
		{
			value[j] = '\0';
			*length = j;
			return (value);
		}
		value = (char *)realloc(value, sizeof(char) * (j + 1));
		value[j] = PATH[*i];
		j++;
		(*i)++;
	}
	j--;
	value[j] = '\0';
	*length = j;
	return (value);
}

/**
 * add_node - Function that adds a node to the end of a linked list.
 * @head: Current head address
 * @dir: New directory to be added to the linked list.
 * @length: Length of the directory
 * Return: Head of the list.
 */
paths *add_node(paths **head, const char *dir, int length)
{
	paths *new_path, *temp;

	new_path = malloc(sizeof(paths));
	if (new_path == NULL)
		return (NULL);

	new_path->directory = strdup(dir);
	new_path->length = length;
	new_path->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_path;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_path;
	}
	return (*head);
}

/**
 * link_path - A function that builds a linked list of the PATH directories.
 */
void link_path(void)
{
	unsigned int i = 0, length = 0, j = 0;
	char *PATH = _getenv("PATH");
	char *dir = NULL;
	paths *head = NULL;

	while (PATH[i] != '\0')
	{
		dir = extract_path(PATH, &i, &length);
		if (dir != NULL)
		{
			head = add_node(&head, dir, length);
		}
		i++;
	}
}
