#include "shell.h"


/**
 * execute_command - executes a command using execve
 * @strArr: array of command arguments
 *
 * Return: exit status of the executed command
 */
int execute_command(char *strArr[])
{
	pid_t id;
	int status = 0;

	id = fork();
	if (id == 0)
	{
		if (execve(strArr[0], strArr, environ) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", strArr[0]);
			exit(127);
		}
	}
	else if (id == -1)
		fprintf(stderr, "./hsh: 1: %s: not found\n", strArr[0]);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}


/**
 * command_existence - checks whether a command exists and executes it
 * @strArr: array of command arguments
 *
 * Return: exit status of the command, or 127 if command not found
 */
int command_existence(char *strArr[])
{
	char *slash_ptr = strchr(strArr[0], '/'), *full_path;
	struct stat st;
	int status = 0;

	if (slash_ptr)
	{
		if (stat(strArr[0], &st) == 0)
		{
			return (execute_command(strArr));
		}
		else
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", strArr[0]);
			return (127);
		}
	}
	full_path = get_command_path(strArr[0]);
	if (full_path)
	{
		strArr[0] = full_path;
		status = execute_command(strArr);
		free(full_path);
		return (status);
	}
	fprintf(stderr, "./hsh: 1: %s: not found\n", strArr[0]);
	return (127);

}
