#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

/**
 * struct args - Struct that stores data on passed arguments.
 * @ac: Argument Count
 * @av: Argument Vector
 * Description: Struct called "args" that stores argument count and vectors
 */
struct args
{
	int ac;
	char **av;
};

/**
 * struct path_s - Singly linked list of PATH directories
 * @directory: Directory
 * @length: Length of the directory
 * @next: Pointer to the next node
 *
 * Description: Singly linked list node structure
 *
 */
typedef struct path_s
{
	char *directory;
	unsigned int length;
	struct path_s *next;
} paths;

extern char **environ;

int lookup(const char *key, char *entry);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
void print_path(void);

char *extract_path(char *PATH, unsigned int *i, unsigned int *length);
void link_path(void);

int _putchar(char c);
ssize_t input(char **lineptr, size_t *n, FILE *stream);
char **_split(char *str, const char *delim, struct args *argp);
char **split(char *str, const char *delim);

#endif
