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
		if (execve(strArr[0], strArr, NULL) == -1)
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
 * get_path - extracts PATH from environment
 *
 * Return: pointer to PATH string or NULL if not found
 */
char *get_path(void)
{
	int i = 0;

	while (environ[i])
	{
		if (!strncmp("PATH=", environ[i], 5))
		{
			return (environ[i]);
		}
		i++;

	}
	return (NULL);
}

/**
 * get_command_path - extracts full path of a command from PATH environment
 * @command: the command name to search for
 *
 * Return: pointer to full path of command or NULL if not found
 */
char *get_command_path(char *command)
{
	char *full_path, *copy_path, *token, *command_path;
	struct stat st;

	full_path = get_path();
	if (!full_path)
		return (NULL);
	copy_path = strdup(full_path + 5);
	if (!copy_path)
		return (NULL);
	token = strtok(copy_path, ":");
	while (token)
	{
		command_path = malloc(strlen(token) + strlen(command) + 2);
		if (!command_path)
		{
			free(copy_path);
			return (NULL);
		}
		strcpy(command_path, token);
		strcat(command_path, "/");
		strcat(command_path, command);
		if (stat(command_path, &st) == 0)
		{
			free(copy_path);
			return (command_path);
		}
		else
			free(command_path);
		token = strtok(NULL, ":");
	}
	free(copy_path);
	return (NULL);
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
