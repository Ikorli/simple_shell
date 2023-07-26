#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

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

char *line = NULL;
int line_pos = 0;

while (1)
{
/*Read more data into the buffer if needed*/
if (buffer_pos >= buffer_size)
{
buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
if (buffer_size <= 0)
{
/* Error or end of file*/
if (line_pos > 0)
{
/* Return the last line if there is any*/
line = realloc(line, line_pos + 1);
if (line == NULL)
{
perror("realloc");
exit(EXIT_FAILURE);
}
line[line_pos] = '\0';
}
return (line);
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
line = realloc(line, line_pos + 1);
if (line == NULL)
{
perror("realloc");
exit(EXIT_FAILURE);
}
line[line_pos] = '\0';
return (line);
}

/* Append the character to the line*/
line = realloc(line, line_pos + 1);
if (line == NULL)
{
perror("realloc");
exit(EXIT_FAILURE);
}
line[line_pos++] = ch;
}
}
}
int cardio(void)
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

