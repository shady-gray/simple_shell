/*Author: Brian Levu*/
#include "shell_main.h"


/**
 * set_working_dir - set the working directory
 * @data: struct for the program's data
 * @dir: path to be set as work directory
 * Return: 0 on success, declared number on failure
 */
int set_working_dir(prog_data *data, char *dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!compare_str(old_dir, dir, 0))
	{
		err_code = chdir(dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_env_var("PWD", dir, data);
	}
	set_env_var("OLDPWD", old_dir, data);
	return (0);
}

/**
 * cd_builtin - changes the current directory
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int cd_builtin(prog_data *data)
{
	char *home_dir = get_env_var("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int err_code = 0;

	if (data->tokens[1])
	{
		if (compare_str(data->tokens[1], "-", 0))
		{
			dir_old = get_env_var("OLDPWD", data);
			if (dir_old)
				err_code = set_working_dir(data, dir_old);
			_print_stdout(get_env_var("PWD", data));
			_print_stdout("\n");

			return (err_code);
		}
		else
		{
			return (set_working_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(old_dir, 128);
		return (set_working_dir(data, home_dir));
	}
	return (0);
}

/**
 * help_builtin - shows help info
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int help_builtin(prog_data *data)
{
	int m, len = 0;
	char *mesarr[6] = {NULL};

	mesarr[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print_stdout(mesarr[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	mesarr[1] = HELP_EXIT_MSG;
	mesarr[2] = HELP_ENV_MSG;
	mesarr[3] = HELP_SETENV_MSG;
	mesarr[4] = HELP_UNSETENV_MSG;
	mesarr[5] = HELP_CD_MSG;

	for (m = 0; mesarr[m]; m++)
	{
		len = _strlen(data->tokens[1]);
		if (compare_str(data->tokens[1], mesarr[m], len))
		{
			_print_stdout(mesarr[m] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * alias_builtin - set, unset and show alias
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int alias_builtin(prog_data *data)
{
	int m = 0;


	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));
	while (data->tokens[++m])
	{
		if (char_count(data->tokens[m], "="))
			set_alias(data->tokens[m], data);
		else
			print_alias(data, data->tokens[m]);
	}

	return (0);
}

/**
 * builtin_ext - exit shell
 * @data: program's data struct
 *
 * Return: 0 on success, declared number on failure
 */
int builtin_ext(prog_data *data)
{
	int m;

	if (data->tokens[1] != NULL)
	{
		m = 0;
		while (data->tokens[1][m])
		{
			if (data->tokens[1][m] != '+' && (data->tokens[1][m] > '9'
			|| data->tokens[1][m] < '0'))
			{
				errno = 2;
				return (2);
			}
			m++;
		}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}
