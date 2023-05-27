/*Author: Brian Levu*/
#include "shell_main.h"

/**
* _logic_ops - split the each line for the logical operators if it exist
* @cmd_arr: command arrays
* @i: cmd_arr index to be checked
* @opr_arr: array of the previous commands logical operators
*
* Return: index of the last command in the cmd_arr.
*/
int _logic_ops(int i, char *cmd_arr[], char opr_arr[])
{
	char *tmp = NULL;
	int j;

	for (j = 0; cmd_arr[i] != NULL  && cmd_arr[i][j]; j++)
	{
		if (cmd_arr[i][j] == '&' && cmd_arr[i][j + 1] == '&')
		{
			tmp = cmd_arr[i];
			cmd_arr[i][j] = '\0';
			cmd_arr[i] = _strdup(cmd_arr[i]);
			cmd_arr[i + 1] = _strdup(tmp + j + 2);
			i++;
			opr_arr[i] = '&';
			free(tmp);
			j = 0;
		}
		if (cmd_arr[i][j] == '|' && cmd_arr[i][j + 1] == '|')
		{
			tmp = cmd_arr[i];
			cmd_arr[i][j] = '\0';
			cmd_arr[i] = _strdup(cmd_arr[i]);
			cmd_arr[i + 1] = _strdup(tmp + j + 2);
			i++;
			opr_arr[i] = '|';
			free(tmp);
			j = 0;
		}
	}

	return (i);
}

/**
* _getline - Read one line of the standard input(user)
* @data: program data's struct
*
* Return: reading count bytes.
*/
int _getline(prog_data *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *cmd_arr[10] = {NULL};
	static char opr_arr[10] = {'\0'};
	ssize_t byte_rd, j = 0;

	if ((!(errno == 0) && opr_arr[0] == '&') || !cmd_arr[0]
		|| (opr_arr[0] == '|' && errno == 0))
	{
		for (j = 0; cmd_arr[j]; j++)
		{
			free(cmd_arr[j]);
			cmd_arr[j] = NULL;
		}

		byte_rd = read(data->file_descriptor, &buffer, BUFFER_SIZE - 1);
		if (byte_rd == 0)
			return (-1);

		j = 0;
		do {
			cmd_arr[j] = _strdup(str_tok(j ? NULL : buffer, "\n;"));
			j = _logic_ops(j, cmd_arr, opr_arr);
		} while (cmd_arr[j++]);
	}

	data->input_line = cmd_arr[0];
	for (j = 0; cmd_arr[j]; j++)
	{
		cmd_arr[j] = cmd_arr[j + 1];
		opr_arr[j] = opr_arr[j + 1];
	}

	return (_strlen(data->input_line));
}
