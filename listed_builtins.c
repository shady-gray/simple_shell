/*Author: Basil Bassey*/
#include "shell_main.h"

/**
 * list_builtins - search for match and execute the associate builtin
 * @data: struct for the program's data
 *
 * Return: Returns the return value of the function executed on success,
 * -1 on failure
 **/
int list_builtins(prog_data *data)
{
	int itr;

	builtins opts[] = {
		{"exit", builtin_ext},
		{"help", help_builtin},
		{"cd", cd_builtin},
		{"alias", alias_builtin},
		{"env", environ_builtin},
		{"setenv", setenv_builtin},
		{"unsetenv", unsetenv_builtin},
		{NULL, NULL}
	};

	itr = 0;
	while (opts[itr].builtin != NULL)
	{
		if (compare_str(opts[itr].builtin, data->cmd_name, 0))
		{
			return (opts[itr].func(data));
		}
		itr++;
	}
	return (-1);
}

