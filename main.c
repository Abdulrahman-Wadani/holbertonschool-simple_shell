#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Reads and executes commands until end-of-file or exit.
 *
 * Return: last executed command status, or 0 if none.
 */
int main(void)
{
	char *buffer = NULL, *strArr[64];
	size_t buf_size = 0;
	ssize_t chars_read;
	int last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		fflush(stdout);
		chars_read = getline(&buffer, &buf_size, stdin);
		if (!buffer || chars_read == -1)
			break;
		tokenize_string(buffer, strArr);
		if (strArr[0])
		{
			if (strcmp(strArr[0], "exit") == 0)
			{
				free(buffer);
				exit(last_status);
			}
			if (strcmp(strArr[0], "env") == 0)
			{
				print_env();
				last_status = 0;
				continue;
			}
			last_status = command_existence(strArr);
		}
	}
	if (buffer)
		free(buffer);
	if (isatty(STDIN_FILENO))
		printf("\n");
	return (last_status);

}
