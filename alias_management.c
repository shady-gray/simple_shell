/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * print_alias - add, remove or show aliases
 * @data: program's data struct
 * @alias: alias
 *
 * Return: 0 on Success, declared number on error
 */
int print_alias(prog_data *data, char *alias)
{
	int m, n, alias_len;
	char buff[250] = {'\0'};

	if (data->alias_list)
	{
		alias_len = _strlen(alias);

		m = 0;
		while (data->alias_list[m])
		{
			if (!alias || (compare_str(data->alias_list[m], alias, alias_len)
				&&	data->alias_list[m][alias_len] == '='))
			{
				for (n = 0; data->alias_list[m][n]; n++)
				{
					buff[n] = data->alias_list[m][n];
					if (data->alias_list[m][n] == '=')
						break;
				}

				buff[m + 1] = '\0';
				append_buffer(buff, "'");
				append_buffer(buff, data->alias_list[m] + n + 1);
				append_buffer(buff, "'\n");
				_print_stdout(buff);
			}
			m++;
		}
	}
	return (0);
}

/**
 * get_alias - get aliases
 * @data: program's data struct
 * @alias: alias
 *
 * Return: 0 on Success, declared number on error
 */
char *get_alias(prog_data *data, char *alias)
{
	int m, alias_len;

	if (alias == NULL || data->alias_list == NULL)
		return (NULL);
	alias_len = _strlen(alias);

	m = 0;
	while (data->alias_list[m])
	{
		if (compare_str(alias, data->alias_list[m], alias_len) &&
			data->alias_list[m][alias_len] == '=')
			return (data->alias_list[m] + alias_len + 1);
		m++;
	}
	return (NULL);

}

/**
 * set_alias - set aliases
 * @str_alias: alias string (alias='value')
 * @data: program's data struct
 *
 * Return: zero if success, or other number if its declared in the arguments
 */
int set_alias(char *str_alias, prog_data *data)
{
	int m, n;
	char buff[250] = {'0'}, *temp = NULL;

	if (data->alias_list == NULL || str_alias == NULL)
		return (1);
	for (m = 0; str_alias[m]; m++)
		if (str_alias[m] != '=')
			buff[m] = str_alias[m];
		else
		{
			temp = get_alias(data, str_alias + m + 1);
			break;
		}

	for (n = 0; data->alias_list[n]; n++)
	{
		if (compare_str(buff, data->alias_list[n], m) &&
			data->alias_list[n][m] == '=')
		{
			free(data->alias_list[n]);
			break;
		}
	}
	if (temp)
	{
		append_buffer(buff, "=");
		append_buffer(buff, temp);
		data->alias_list[n] = _strdup(buff);
	}
	else
		data->alias_list[n] = _strdup(str_alias);
	return (0);
}
