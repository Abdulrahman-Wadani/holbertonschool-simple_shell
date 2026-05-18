#include "shell.h"

/**
 * execute_command - Forks a child process and runs the given command
 *                   via execve. Parent waits for child to finish.
 * @command: Full path of the executable (e.g. "/bin/ls").
 *
 * Return: void. Prints error via perror if execve fails.
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
 * main - Entry point. Reads lines from stdin, runs each as a command.
 *
 * Return: 0 on normal exit (EOF / Ctrl+D).
 */
int main(void)
{
	char *line = NULL;
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

		if (line[0] == '\0')
			continue;

		execute_command(line);
	}

	free(line);
	return (0);
}
