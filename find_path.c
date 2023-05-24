/*Author: Brian Levu*/
#include "shell_main.h"

int file_check(char *path);

/**
 * file_check - checks if exists a file
 * @path: pointer to file (path)name
 *
 * Return: 0 on success, or error code if it exists.
 */
int file_check(char *path)
{
	struct stat fc;

	if (stat(path, &fc) != -1)
	{
		if (S_ISDIR(fc.st_mode) ||  access(path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}

/**
 * program_finder - find a program in path
 * @data: program's data struct
 *
 * Return: 0 if success, errcode otherwise
 */
int program_finder(prog_data *data)
{
	int ret_code = 0, m = 0;
	char **dirs;

	if (!data->cmd_name)
		return (2);
	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (file_check(data->cmd_name));
	free(data->tokens[0]);
	data->tokens[0] = _strconcate(_strdup("/"), data->cmd_name);
	if (!data->tokens[0])
		return (2);
	dirs = tok_path(data);
	if (!dirs[0] || !dirs)
	{
		errno = 127;
		return (127);
	}
	m = 0;
	while (dirs[m])
	{
		dirs[m] = _strconcate(dirs[m], data->tokens[0]);
		ret_code = file_check(dirs[m]);
		if (ret_code == 0 || ret_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = _strdup(dirs[m]);
			free_arr_of_arr(dirs);
			return (ret_code);
		}
		m++;
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_arr_of_arr(dirs);
	return (ret_code);
}

/**
 * tok_path - tokenize the path in dirs
 * @data: a pointer to the program's data
 *
 * Return: path dirs array
 */
char **tok_path(prog_data *data)
{
	int m = 0;
	int dirs_count = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = get_env_var("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = _strdup(PATH);
	for (m = 0; PATH[m]; m++)
	{
		if (PATH[m] == ':')
			dirs_count++;
	}

	tokens = malloc(dirs_count * sizeof(char *));
	m = 0;
	tokens[m] = _strdup(str_tok(PATH, ":"));
	while (tokens[m++])
	{
		tokens[m] = _strdup(str_tok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;

	return (tokens);

}

