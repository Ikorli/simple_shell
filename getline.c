#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
static int read_input(char *buffer, int size);
static char *process_input(const char *buffer, int size);

/**
 * our_getline - Read a line of input from the user.
 *
 * Return: A pointer to the line on success, NULL on error or EOF.
 */
char *our_getline(void)
{
static char buffer[BUFFER_SIZE];
static int buffer_pos;
static int buffer_size;

while (1)
{
/* Read more data into the buffer if needed*/
if (buffer_pos >= buffer_size)
{
buffer_size = read_input(buffer, BUFFER_SIZE);
if (buffer_size <= 0)
{
/* Error or end of file*/
return (process_input(buffer, buffer_pos));
}
buffer_pos = 0;
}

/* Process the characters in the buffer*/
while (buffer_pos < buffer_size)
{
char ch = buffer[buffer_pos++];
if (ch == '\n')
{
/* Found the end of the line, return the line*/
return (process_input(buffer, buffer_pos));
}
}
}
}

/**
 * read_input - Read data from stdin into the buffer.
 *
 * @buffer: The buffer to store the read data.
 * @size: The size of the buffer.
 *
 * Return: Number of bytes read.
 */
static int read_input(char *buffer, int size)
{
int bytes_read = read(STDIN_FILENO, buffer, size);
if (bytes_read < 0)
{
perror("read");
exit(EXIT_FAILURE);
}
return (bytes_read);
}

/**
 * process_input - Process the input buffer and return the line.
 *
 * @buffer: The input buffer.
 * @size: The size of the buffer.
 *
 * Return: Pointer to the line.
 */
static char *process_input(const char *buffer, int size)
{
char *line = malloc(size + 1);
if (line == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
memcpy(line, buffer, size);
line[size] = '\0';
return (line);
}

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int great(void)
{
char *line;
while ((line = our_getline()) != NULL)
{
write(STDOUT_FILENO, "You entered: ", 13);
write(STDOUT_FILENO, line, strlen(line));
write(STDOUT_FILENO, "\n", 1);
free(line);
}

return (0);
}

