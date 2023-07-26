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

void display_prompt(void);
int read_command(char *cmd);
char **tokenize_command(char *cmd);
void execute_command(char *cmd);
void handle_command_line_arguments(int argc, char *argv[]);
void exit_shell(void);
void print_environment(void);
char *get_command_path(char *command);
extern char **environ;
#endif
