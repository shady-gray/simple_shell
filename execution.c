/*Author: Brian Levu*/
#include "shell_main.h"

/**
 * exec_cmd - exec_cmd a command using its entire path variables.
 * @data: a pointer to the program's data's struct
 *
 * Return: returns zero on success, return -1 on failure.
 */
int exec_cmd(prog_data *data)
{
        int ret_value = 0, stat;
        pid_t pidd;

        ret_value = list_builtins(data);
        if (ret_value != -1)
                return (ret_value);
        ret_value = program_finder(data);
        if (ret_value)
                return (ret_value);
        else if (!ret_value)
        {
                pidd = fork();
                if (pidd == -1)
                {
                        perror(data->cmd_name);
                        exit(EXIT_FAILURE);
                }
                if (pidd == 0)
                {
                        ret_value = execve(data->tokens[0], data->tokens, data->env);
                        if (ret_value == -1)
                                perror(data->cmd_name), exit(EXIT_FAILURE);
                }
                else
                {
                        wait(&stat);
                        if (WIFEXITED(stat))
                                errno = WEXITSTATUS(stat);
                        else if (WIFSIGNALED(stat))
                                errno = WTERMSIG(stat) + 128;
                }
        }
        return (0);
}
