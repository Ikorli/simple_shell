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

define MAX_COMMAND_LENGHT 100

// function prototypes
void display_prompt(void);
int read_command(char *cmd);
void execute_command(char *cmd);
