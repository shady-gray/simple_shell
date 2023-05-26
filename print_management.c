/*Author: Basil Bassey*/
#include "shell_main.h"

/**
 * _print_stdout - writes a char array on the standard output
 * @str: pointer string
 *
 * Return: bytes written (wr). On error, -1 is returned
 */
int _print_stdout(char *str)
{
	ssize_t wr;

	wr = write(STDOUT_FILENO, str, _strlen(str));
	return (wr);
}

/**
 * _print_stderr - writes a array of chars to the standard error
 * @str: pointer to string
 *
 * Return: bytes written (wr). On error, -1 is returned
 */
int _print_stderr(char *str)
{
	ssize_t wr;

	wr = write(STDERR_FILENO, str, _strlen(str));
	return (wr);
}

/**
 * _print_error - writes a array of chars in the standard error
 * @data: program's data struct
 * @err_code: error code
 *
 * Return: bytes written (wr). On error, -1 is returned
 */
int _print_error(int err_code, prog_data *data)
{
	char no_string[10] = {'\0'};

	longint_to_str((long) data->execution_count, no_string, 10);

	if (err_code == 2 || err_code == 3)
	{
		_print_stderr(data->prog_name);
		_print_stderr(": ");
		_print_stderr(no_string);
		_print_stderr(": ");
		_print_stderr(data->tokens[0]);
		if (err_code == 2)
			_print_stderr(": Illegal number: ");
		else
			_print_stderr(": can't cd to ");
		_print_stderr(data->tokens[1]);
		_print_stderr("\n");
	}
	else if (err_code == 127)
	{
		_print_stderr(data->prog_name);
		_print_stderr(": ");
		_print_stderr(no_string);
		_print_stderr(": ");
		_print_stderr(data->cmd_name);
		_print_stderr(": not found\n");
	}
	else if (err_code == 126)
	{
		_print_stderr(data->prog_name);
		_print_stderr(": ");
		_print_stderr(no_string);
		_print_stderr(": ");
		_print_stderr(data->cmd_name);
		_print_stderr(": Permission denied\n");
	}
	return (0);
}

