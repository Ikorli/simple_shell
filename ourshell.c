#include "shell.h"
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

/**
 * handle_command_line_arguments - Handle command line arguments for the shell.
 * @argc: The argument count.
 * @argv: An array of strings containing the command line arguments.
 *
 * Return: None.
 */
void handle_command_line_arguments(int argc, char *argv[])
{
int i;

/* Handle command line arguments for the shell */
for (i = 1; i < argc; i++)
{
if (access(argv[i], F_OK) == 0)
{
/* Process the option (e.g., display help, set flags, etc.) */
/* For this example, we will just print the option */
write(STDOUT_FILENO, "Option: ", 8);
write(STDOUT_FILENO, argv[i], strlen(argv[i]));
write(STDOUT_FILENO, "\n", 1);
}
else
{
/* Handle the case when the option is not recognized */
write(STDOUT_FILENO, "Unknown option: ", 16);
write(STDOUT_FILENO, argv[i], strlen(argv[i]));
write(STDOUT_FILENO, "\n", 1);
}
}
}

/**
 * main - Entry point for the simple shell program.
 * @argc: The argument count used.
 * @argv: An array of stings containing the command line arguments unused.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	char cmd[MAX_COMMAND_LENGTH];

handle_command_line_arguments(argc, argv);


	while (1)
	{
		/* Display the prompt */
		display_prompt();

		/* Read the user input */
		if (read_command(cmd) == 0)
		{
			/* If read_command returns 0, it means the user entered Ctrl+D (EOF) */
			write(STDOUT_FILENO, "Exiting shell\n", 14);
			break;
		}

		/* Execute the command */
		execute_command(cmd);
	}

	return (0);
}

/**
 * display_prompt - Function to display the prompt.
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "OurShell> ", 10);
}

/**
 * read_command - Read command from standard input.
 * @cmd: A character array to store the user input.
 *
 * Return: 1 on success, 0 on reaching (EOF) Ctrl+D.
 */
int read_command(char *cmd)
{
	if (fgets(cmd, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		/* If fgets returns NULL, it means the user entered Ctrl+D (EOF) */
		return (0);
	}

	/* Remove the newline character at the end of the command */
	cmd[strcspn(cmd, "\n")] = '\0';
	return (1);
}

/**
 * execute_command - Function to execute the command.
 * @cmd: The command to be executed.
 */
void execute_command(char *cmd)
{
	/* Fork a new process to execute the command */
	pid_t pid = fork();

	if (pid < 0)
	{
		/* Fork failed */
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */

		/* Tokenize the command to get the program name and arguments */
		char *token = strtok(cmd, " ");
		char *argv[MAX_COMMAND_LENGTH];
		int i = 0;

		while (token != NULL)
		{
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		/* Execute the command using execvp */
		if (access(argv[0], X_OK) == 0)
		{
			execvp(argv[0], argv);
		}
		else
		{
			/* If access returns non-zero, the command was not found */
			write(STDOUT_FILENO, "Command not found\n", 18);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */

		/* Wait for the child process to complete */
		int status;

		waitpid(pid, &status, 0);
	}
}

