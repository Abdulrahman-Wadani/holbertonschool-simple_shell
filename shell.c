#include "shell.h"

/**
 * trim_whitespace - Strip leading and trailing spaces and tabs.
 * @str: String to trim (trailing whitespace is modified in place).
 *
 * Return: Pointer to the first non-whitespace character. Returns an
 * empty string if the entire input was whitespace.
 */
char *trim_whitespace(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (str);
}

/**
 * execute_command - Forks a child process and runs the given command
 *                   via execve. Parent waits for child to finish.
 * @command: Full path of the executable (e.g. "/bin/ls").
 *
 * Return: Nothing.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;

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
 * Description: Prints a prompt, reads one command per line from stdin,
 * trims surrounding whitespace, and executes each via fork + execve.
 * Exits on EOF (Ctrl+D).
 *
 * Return: 0 on normal exit.
 */
int main(void)
{
	char *line = NULL;
	char *trimmed;
	size_t cap = 0;
	ssize_t nread;

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

		trimmed = trim_whitespace(line);

		if (trimmed[0] == '\0')
			continue;

		execute_command(trimmed);
	}

	free(line);
	return (0);
}