
#ifndef SHELL_MAIN_H
#define SHELL_MAIN_H

/*Author: Basil Bassey*/

#include "shell_macros.h"

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


/**
 * struct info- struct for the program's data
 * @prog_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @cmd_name: pointer to the first command typed by the user
 * @execution_count: number of executed commands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *prog_name;
	char *input_line;
	char *cmd_name;
	int execution_count;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} prog_data;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @func: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*func)(prog_data *data);
} builtins;


/* shell_main.c functions*/
void data_initialization(prog_data *data, int arc, char *argv[], char **env);
void ctrlc_handler(int opr UNUSED);
void prompt_loop(prog_data *data, char *pmt);

/* _getline.c functions */
int _logic_ops(int i, char *array_commands[], char array_operators[]);
int _getline(prog_data *data);

/* expand.c functions */
int append_buffer(char *buff, char *str);
void variables_expand(prog_data *data);
void alias_expand(prog_data *data);

/* _strtok.c functions */
char *str_tok(char *line, char *delim);
void tokenize(prog_data *data);

/* execution.c functions */
int exec_cmd(prog_data *data);

/* listed_builtin.c functions */
int list_builtins(prog_data *data);

/* extra_builtin.c functions*/
int set_working_dir(prog_data *data, char *dir);
int cd_builtin(prog_data *data);
int help_builtin(prog_data *data);
int alias_builtin(prog_data *data);
int builtin_ext(prog_data *data);

/* environ_builtin.c functions */
int environ_builtin(prog_data *data);
int setenv_builtin(prog_data *data);
int unsetenv_builtin(prog_data *data);

/* find_path.c functions*/
int program_finder(prog_data *data);
char **tok_path(prog_data *data);

/* free_mem_management.c functions */
void free_arr_of_arr(char **arr);
void free_recurring_data(prog_data *data);
void free_all_data(prog_data *data);

/* env-var_management.c functions*/
void print_env(prog_data *data);
char *get_env_var(char *var, prog_data *data);
int set_env_var(char *var, char *val, prog_data *data);
int remove_env_var(char *var, prog_data *data);

/* print_management.c functions */
int _print_stdout(char *str);
int _print_stderr(char *str);
int _print_error(int err_code, prog_data *data);

/* string_management.c functions */
int _strlen(char *str);
char *_strdup(char *str);
int compare_str(char *str1, char *str2, int num);
char *_strconcate(char *str1, char *str2);
void _strrev(char *str);

/* numbers_management.c functions*/
int _atoi(char *str);
void longint_to_str(long num, char *buff_str, int base);
int char_count(char *str, char *chars);


/* alias_management.c functions */
int print_alias(prog_data *data, char *alias);
char *get_alias(prog_data *data, char *alias);
int set_alias(char *str_alias, prog_data *data);

#endif /* ifndef SHELL_MAIN_H */

