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

#define MAX_COMMAND_LENGHT 100



/* Structure for linked list */
typedef struct list_s
{
char *str;
struct list_s *next;
list_t;
}

typedef struct info_s
{
list_t *alias; /* Linked list for aliases */
info_t;
list_t *history; /* Linked list for history */
}

/* Function prototypes */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

#endif
