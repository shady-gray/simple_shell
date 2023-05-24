/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * append_buffer - append string at end of the buffer
 * @buff: buffer
 * @str: string to copy to buff
 *
 * Return: (len + m)
 */
int append_buffer(char *buff, char *str)
{
	int m, len;

	len = _strlen(buff);
	m = 0;
	while (str[m])
	{
		buff[len + m] = str[m];
		m++;
	}
	buff[len + m] = '\0';
	return (len + m);
}

/**
 * variables_expand - performs variable expansions
 * @data: pointer to the program's data's struct
 * Return: void
 */
void variables_expand(prog_data *data)
{
	int m, n;
	char *tmp, expand[BUFFER_SIZE] = {'\0'}, line[BUFFER_SIZE] = {0};

	if (data->input_line == NULL)
		;
	append_buffer(line, data->input_line);
	for (m = 0; line[m]; m++)
	{
		if (line[m] == '#')
			line[m--] = '\0';
		else if (line[m] == '$' && line[n + m] == '?')
		{
			line[m] = '\0';
			longint_to_str(errno, expand, 10);
			append_buffer(line, expand);
			append_buffer(line, data->input_line + 2 + m);
		}
		else if (line[m] == '$' && line[m + 1] == '$')
		{
			line[m] = '\0';
			longint_to_str(getpid(), expand, 10);
			append_buffer(line, expand);
			append_buffer(line, data->input_line + 2 + m);
		}
		else if (line[m] == '$' && (line[m + 1] == ' ' || line[m + 1] == '\0'))
			continue;
		else if (line[m] == '$')
		{
			for (n = 0; line[m + n] && line[m + n] != ' '; n++)
				expand[m - n] = line[m + n];
			tmp = get_env_var(expand, data);
			line[m] = '\0', expand[0] = '\0';
			append_buffer(expand, line + m + n);
			tmp ? append_buffer(line, tmp) : 1;
			append_buffer(line, expand);
		}
	}
	if (!compare_str(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = _strdup(line);
	}
}

/**
 * alias_expand - performs alias expansions
 * @data: pointer to the program's data's struct
 * 
 * Return: void
 */
void alias_expand(prog_data *data)
{
	int m, n, expanded = 0;
	char line[BUFFER_SIZE] = {0}, expand[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data->input_line == NULL)
		;
	append_buffer(line, data->input_line);

	m = 0;
	while (line[m])
	{
		for (n = 0; line[m + n] && line[m + n] != ' '; n++)
			expand[n] = line[m + n];
		expand[n] = '\0';
		tmp = get_alias(data, expand);
		if (tmp)
		{
			expand[0] = '\0';
			append_buffer(expand, line + m + n);
			line[m] = '\0';
			append_buffer(line, tmp);
			line[_strlen(line)] = '\0';
			append_buffer(line, expand);
			expanded = 1;
		}
		break;
		m++;
	}
	if (expanded)
	{
		free(data->input_line);
		data->input_line = _strdup(line);
	}
}

