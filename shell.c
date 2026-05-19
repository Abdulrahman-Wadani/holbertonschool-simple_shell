#include "shell.h"

/**
 * tokenize - Split a line into tokens separated by whitespace.
 * @line: The input string (modified in place by strtok).
 * @argv: Output array to fill with token pointers.
 * @max: Size of the argv array.
 *
 * Return: Number of tokens parsed (excluding the NULL terminator).
 */
int tokenize(char *line, char **argv, int max)
{
	int count = 0;
	char *token;

	token = strtok(line, " \t");
	while (token != NULL && count < max - 1)
	{
		argv[count] = token;
		count++;
		token = strtok(NULL, " \t");
	}
	argv[count] = NULL;
	return (count);
}

/**
 * execute_command - Forks a child process and runs a command via execve.
 * @argv: NULL-terminated array of arguments (argv[0] is the command).
 *
 * Return: Nothing.
 */
void execute_command(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("./hsh");
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * main - Entry point for the simple shell.
 *
 * Description: Prints a prompt, reads one line per command, tokenizes
 * by whitespace, and executes via fork + execve. Exits on EOF.
 *
 * Return: 0 on normal exit.
 */
int main(void)
{
	char *line = NULL;
	char *argv[64];
	size_t cap = 0;
	ssize_t nread;
	int n;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&line, &cap, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		n = tokenize(line, argv, 64);
		if (n == 0)
			continue;

		execute_command(argv);
	}

	free(line);
	return (0);
}
