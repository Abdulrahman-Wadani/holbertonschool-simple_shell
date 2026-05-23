#include "shell.h"


/**
 * tokenize_string - tokenizes a string into an array
 * @str: the string to tokenize
 * @strArr: array to store tokens
 *
 * Return: void
 */
void tokenize_string(char *str, char *strArr[])
{
	char *token = strtok(str, "\n\t ");
	int i = 0;

	while (token)
	{
		strArr[i] = token;

		token = strtok(NULL,  "\n\t ");
		i++;
	}
	strArr[i] = NULL;
}
