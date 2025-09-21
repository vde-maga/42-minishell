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

int ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd)
{
    pid_t   pid;
    int     status;

    if (!cmd || !cmd->args || !cmd->args[0])
        return (0);
    if (ft_exec_is_builtin(cmd->args[0]))
    {
        // TODO: Create logic to run the builtin
        ft_printf("minishell: \"%s\" is a builtin\n", cmd->args[0]);
        return (0);
    }
    pid = fork();
    if (pid == -1)
    {
        ft_printf("fork failed: %s\n", strerror(errno));
        ms_data->exit_status = 1;
        return (1);
    }
    if (pid == 0)
    {
        if (ft_exec_replace_cmd_with_path(ms_data, cmd))
            execve(cmd->args[0], cmd->args, ms_data->env);
        ft_printf("execve failed: %s\n", strerror(errno));
        _exit(127);
    }
     waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        ms_data->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        ms_data->exit_status = 128 + WTERMSIG(status);
    return ms_data->exit_status;
}