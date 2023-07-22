#include <stdio.h>

/**
 * main - Entry point for the program
 *
 * This function serves as the entry point for the program.
 * It prompts the user to enter their name, reads the input,
 * and prints a personalized greeting.
 *
 * Return: 0 on successful execution, non-zero otherwise
 */
int main(void)
{
char name[100];

write("What is your name? ");
getline("%s", name);

write("Hello, %s!\n", name);

return (0);
}

