/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * environ_builtin - shows the environment where the shell runs
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int environ_builtin(prog_data *data)
{
	int m;
	char cp_name[50] = {'\0'};
	char *cpy_var = NULL;

	if (data->tokens[1] == NULL)
		print_env(data);
	else
	{
		m = 0;
		while (data->tokens[1][m])
		{
			if (data->tokens[1][m] == '=')
			{
				cpy_var = _strdup(get_env_var(cp_name, data));
				if (cpy_var != NULL)
					set_env_var(cp_name, data->tokens[1] + m + 1, data);
				print_env(data);
				if (get_env_var(cp_name, data) == NULL)
				{
					_print_stdout(data->tokens[1]);
					_print_stdout("\n");
				}
				else
				{
					set_env_var(cp_name, cpy_var, data);
					free(cpy_var);
				}
				return (0);
			}
			cp_name[m] = data->tokens[1][m];
			m++;
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}

	return (0);
}

/**
 * setenv_builtin - create or override a variable of environment
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int setenv_builtin(prog_data *data)
{
	if (data->tokens[2] == NULL || data->tokens[1] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	set_env_var(data->tokens[1], data->tokens[2], data);
	return (0);
}

/**
 * unsetenv_builtin - delete a variable of environment
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int unsetenv_builtin(prog_data *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2])
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	remove_env_var(data->tokens[1], data);

	return (0);
}
