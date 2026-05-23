#include "shell.h"

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
