#include "minishell.h"

int ft_exec_is_builtin(char *cmd)
{
    if (!cmd) 
        return 0;
    if (!ft_strcmp(cmd, "cd")) 
        return 1;
    // if (!ft_strcmp(cmd, "echo")) 
    //     return 1;
    // if (!ft_strcmp(cmd, "pwd")) 
    //     return 1;
    if (!ft_strcmp(cmd, "export")) 
        return 1;
    if (!ft_strcmp(cmd, "unset")) 
        return 1;
    if (!ft_strcmp(cmd, "env")) 
        return 1;
    if (!ft_strcmp(cmd, "exit")) 
        return 1;
    return 0;
}

int ft_exec_run_builtin(t_minishell *ms_data, char **args)
{
    int exit_code;
    (void)ms_data;
    (void)args;

    // TODO: This function need to execute the builtin and to return the exit_code 
    exit_code = 0;
    return (exit_code);
}
