/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * str_tok - Creates a pointer to a tokenized string
 * @line: pointer to array received from getline
 * @delim: characters used to mark off string in parts
 *
 * Return: pointer to created token
*/
char *str_tok(char *line, char *delim)
{
	int m;
	static char *str;
	char *cpy_str;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		m = 0;
		while (delim[m] != '\0')
		{
			if (*str == delim[m])
			break;
			m++;
		}
		if (delim[m] == '\0')
			break;
	}

	cpy_str = str;
	if (*cpy_str == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (m = 0;  delim[m] != '\0'; m++)
		{
			if (*str == delim[m])
			{
				*str = '\0';
				str++;
				return (cpy_str);
			}
		}
	}
	return (cpy_str);
}

/**
 * tokenize - separate string using a designed delim
 * @data: pointer to the program's data's struct
 * 
 * Return: void
 */
void tokenize(prog_data *data)
{
	char *delim = " \t";
	int m, n, len, count = 2;

	len = _strlen(data->input_line);
	if (len)
	{
		if (data->input_line[len - 1] == '\n')
			data->input_line[len - 1] = '\0';
	}

	m = 0;
	while (data->input_line[m])
	{
		for (n = 0; delim[n]; n++)
		{
			if (data->input_line[m] == delim[n])
				count++;
		}
		m++;
	}

	data->tokens = malloc(sizeof(char *) * count);
	if (data->tokens == NULL)
	{
		perror(data->prog_name);
		exit(errno);
	}
	m = 0;
	data->tokens[m] = str_duplicate(str_tok(data->input_line, delim));
	data->cmd_name = str_duplicate(data->tokens[0]);
	while (data->tokens[m++])
	{
		data->tokens[m] = str_duplicate(str_tok(NULL, delim));
	}
}

