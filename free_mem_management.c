/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * free_arr_of_arr - frees up arrays of arrays
 * @arr: pointer to pointers of array
 *
 * Return: void
 */
void free_arr_of_arr(char **arr)
{
	int m;

	if (arr != NULL)
	{
		for (m = 0; arr[m]; m++)
			free(arr[m]);

		free(arr);
		arr = NULL;
	}
}

/**
 * free_recurring_data - frees up recurrent data
 * @data: program's data struct
 *
 * Return: void
 */
void free_recurring_data(prog_data *data)
{
	if (data->tokens)
		free_arr_of_arr(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->cmd_name)
		free(data->cmd_name);

	data->input_line = NULL;
	data->cmd_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: program's data struct
 *
 * Return: void
 */
void free_all_data(prog_data *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->prog_name);
	}
	free_recurring_data(data);
	free_arr_of_arr(data->env);
	free_arr_of_arr(data->alias_list);
}

