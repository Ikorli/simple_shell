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

#define MAX_COMMAND_LENGTH 100

/* Function prototypes */
void display_prompt(void);
int read_command(char *cmd);
void execute_command(char *cmd);
void handle_command_line_arguments(int argc, char *argv[]);
void exit_shell(void);
void print_environment(void);
char *get_command_path(char *command);

/**
 * get_command_path - Function to get the full path of a command.
 * @command: The command for which to find the path.
 *
 * Return: Pointer to the path of the command, or NULL if not found.
 */
char *get_command_path(char *command)
{
char *path = getenv("PATH");
char *path_copy, *token;
char *full_path;
if (path == NULL)
{
return (NULL);
}
path_copy = strdup(path);
if (path_copy == NULL)
{
perror("strdup");
exit(EXIT_FAILURE);
}
token = strtok(path_copy, ":");
while (token != NULL)
{
/* Create the full path of the command */
full_path = malloc(strlen(token) + strlen(command) + 2);
if (full_path == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
strcpy(full_path, token);
strcat(full_path, "/");
strcat(full_path, command);

/* Check if the command exists at this path */
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (full_path);
}

free(full_path);
token = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
