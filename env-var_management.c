/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * print_env - prints the current environ
 * @data: program's data struct
 *
 * Return: void
 */
void print_env(prog_data *data)
{
	int i;

	i = 0;
	while (data->env[i])
	{
		_print_stdout(data->env[i]);
		_print_stdout("\n");
	}
	i++;
}

/**
 * get_env_var - gets the val of an environment variable
 * @var: variable
 * @data: program's data struct
 *
 * Return: pointer to the variable val or NULL if it doesn't exist
 */
char *get_env_var(char *var, prog_data *data)
{
	int m, var_len = 0;

	if (var == NULL || data->env == NULL)
		return (NULL);
	var_len = _strlen(var);

	m = 0;
	while (data->env[m])
	{
		if (data->env[m][var_len] == '='
		    && compare_str(var, data->env[m], var_len))
		{
			return (data->env[m] + var_len + 1);
		}
		m++;
	}

	return (NULL);
}

/**
 * set_env_var - overwrites the environment variable value
 * or create it if does not exist.
 * @var: name of the variable to set
 * @val: new value
 * @data: program's data struct
 *
 * Return: 0 on success, 1 if NULL parameter 2 if error
 */
int set_env_var(char *var, char *val, prog_data *data)
{
	int m, var_len = 0, new_var = 1;

	if (val == NULL || data->env == NULL  || var == NULL)
		return (1);
	var_len = _strlen(var);

	m = 0;
	while (data->env[m])
	{
		if (compare_str(var, data->env[m], var_len) &&
		 data->env[m][var_len] == '=')
		{
			new_var = 0;
			free(data->env[m]);
			break;
		}
		m++;
	}
	data->env[m] = _(_strdup(var), "=");
	data->env[m] = _(data->env[m], val);

	if (new_var)
	{
		data->env[m + 1] = NULL;
	}
	return (0);
}

/**
 * remove_env_var - delete an environment variable
 * @var: variable
 * @data: program's data struct
 *
 * Return: 1 if var removed, 0 if var does not exist;
 */
int remove_env_var(char *var, prog_data *data)
{
	int m, var_len = 0;

	if (var == NULL || data->env == NULL)
		return (0);
	var_len = _strlen(var);

	m = 0;
	while (data->env[m])
	{
		if (compare_str(var, data->env[m], var_len) &&
		 data->env[m][var_len] == '=')
		{
			free(data->env[m]);
			m++;
			for (; data->env[m]; m++)
			{
				data->env[m - 1] = data->env[m];
			}
			data->env[m - 1] = NULL;
			return (1);
		}
		m++;
	}
	return (0);
}

