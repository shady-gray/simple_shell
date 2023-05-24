/*Author: Basil Bassey*/
#include "shell_main.h"
/**
 * data_initialization - uses program info to initialize struct
 * @data: pointer to data struct
 * @argc: no of command line values received
 * @argv: Array of arguments
 * @env: NULL terminated array of strings
 *
 * Returns: void
 */
void data_initialization(prog_data *data, int argc, char *argv[], char **env)
{
	int j = 0;

	data->prog_name = argv[0];
	data->input_line = NULL;
	data->cmd_name = NULL;
	data->execution_count = 0;
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_print_stderr(data->prog_name);
			_print_stderr(": 0: Can't open ");
			_print_stderr(argv[1]);
			_print_stderr("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(50 * sizeof(char *));
	if (env != NULL)
	{
		while (env[j])
		{
			data->env[j] = _strdup(env[j]);
			j++;
		}
	}
	data->env[j] = NULL;
	env = data->env;
	data->alias_list = malloc(20 * sizeof(char *));

	j = 0;
	while (j < 20)
	{
		data->alias_list[j] = NULL;
		j++;
	}
}
/**
 * ctrlc_handler - prints prompts in new line after previous command execution
 * @UNUSED: option of the prototype
 *
 * Return: void
 */
void ctrlc_handler(int opt UNUSED)
{
	_print_stdout("\n");
	_print_stdout(PROMPT_MSG);
}


/**
 * prompt_loop - an infinite loop that shows the prompt
 * @data: an infinite loop of prompt
 * @pmt: printed prompt
 *
 * Return: void
 */
void prompt_loop(prog_data *data, char *pmt)
{
	int err_code = 0;
	int str_len = 0;

	while (++(data->execution_count))
	{
		_print_stdout(pmt);
		err_code = str_len = _getline(data);

		if (err_code == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (str_len >= 1)
		{
			alias_expand(data);
			variables_expand(data);
			tokenize(data);
			if (data->tokens[0])
			{
				err_code = exec_cmd(data);
				if (err_code != 0)
					_print_error(err_code, data);
			}
			free_recurring_data(data);
		}
	}
}

/**
 * main - Begin the shell program
 * @argc: no of command line values received
 * @argv: Array of command line values received from user
 * @env: NULL terminated array of strings
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	prog_data data_struct = {NULL}, *data = &data_struct;
	char *pmt = "";

	data_initialization(data, argc, argv, env);

	signal(SIGINT, ctrlc_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;/*???????*/
		pmt = PROMPT_MSG;
	}
	errno = 0;
	prompt_loop(data, pmt);
	return (0);
}

