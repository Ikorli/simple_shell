#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>

#define MAX_COMMAND_LENGTH 100

/**
 * struct list_s - Structure for a linked list node.
 * @str: The string element of the node.
 * @next: Pointer to the next node.
 *
 * Description: This structure represents a node in a linked list.
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct info_s - Structure to store shell information.
 * @alias: Linked list for aliases.
 * @history: Linked list for history.
 *
 * Description: This structure is used to store information
 *              and maintain state for the shell program.
 */
typedef struct info_s
{
	list_t *alias;
	list_t *history;
} info_t;

/* Function prototypes */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

#endif
