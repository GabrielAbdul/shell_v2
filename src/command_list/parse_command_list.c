#include "../shell.h"

/**
 * get_path - finds if command is in path
 * @command: command string
 * Return: int
 */
char *get_path(char *command)
{
	int i;
	char *tokens, *path;
	char *PATHS, **path_directories;

	if (_strstr(command, "/"))
		return (_strdup(command));

	path_directories =  malloc(sizeof(char *) * PATH_SIZE);
	if (!path_directories)
	{
		perror("malloc");
		return (NULL);
	}

	PATHS = _strdup(_getenv("PATH"));

	tokens = strtok(PATHS, ":");
	path_directories[0] = tokens;

	for (i = 1; (tokens = strtok(NULL, ":")); i++)
		path_directories[i] = tokens;
	path_directories[i] = NULL;

	path = search_path_directories(path_directories, command, i);

	free(path_directories);
	free(PATHS);

	return (path);
}
/**
 * search_path_directories - finds if command is in path
 * @dirs: directories
 * @command: command string
 * @size: size
 * Return: path
 */
char *search_path_directories(char **dirs, char *command, int size)
{
	int i;
	DIR *dir;
	struct dirent *read;
	char *path = NULL;

	for (i = 0; i < size; i++)
	{
		dir = opendir(dirs[i]);
		if (dir == NULL)
			return (NULL);
		while ((read = readdir(dir)))
		{
			if (_strcmp(read->d_name, command) == 0)
			{
				path = malloc(sizeof(char) * (_strlen(dirs[i]) + _strlen(command) + 2));
				/* sprintf the path dir to the command name */
				sprintf(path, "%s/%s", dirs[i], command);
				closedir(dir);
				return (path);
			}
		}
		closedir(dir);
	}
	return (path);
}
