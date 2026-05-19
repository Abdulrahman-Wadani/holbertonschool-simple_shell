#include "shell.h"

/**
 * main - description
 *
 * Return: Return: 0 on success
 */
int main(void)
{
	char *buffer = NULL, *strArr[64];
	size_t buf_size = 0;
	ssize_t chars_read;

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		chars_read = getline(&buffer, &buf_size, stdin);
		if (!buffer || chars_read == -1)
			break;
		tokenize_string(buffer, strArr);
		if (strArr[0] == "exit")
			exit(EXIT_SUCCESS);
		command_existence(strArr);
	}
	if (buffer)
		free(buffer);
	printf("\n");
	return (0);

}
