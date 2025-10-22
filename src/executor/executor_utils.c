#include "minishell.h"

int ft_exec_is_builtin(char *cmd)
{
    if (!cmd) 
        return 0;
    if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
        || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
            || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
                || !ft_strcmp(cmd, "exit")) 
        return 1;
    return 0;
}

int ft_exec_run_builtin(t_minishell *ms_data, char **args)
{
    int exit_code;
    (void)ms_data;
    (void)args;

    // TODO: Check correct exit code 
    if (args == NULL || args[0] == NULL)
        return (0);

    if (ft_strcmp(args[0], "pwd") == 0)
        exit_code = ft_builtin_pwd();
    else if (ft_strcmp(args[0], "cd") == 0)
        exit_code = ft_builtin_cd(ms_data, args[1]);
    else if (ft_strcmp(args[0], "echo") == 0)
        exit_code = ft_builtin_echo(args);
    else if (ft_strcmp(args[0], "unset") == 0)
        exit_code = ft_builtin_unset(ms_data, args[1]);
    else if (ft_strcmp(args[0], "env") == 0)
        exit_code = ft_builtin_env(ms_data);
    else
        exit_code = -1;
    // else if (ft_strcmp(args[0], "export") == 0)
    // {
    //     exit_code = ft_export(args, ms_data);
    // }
    // else if (ft_strcmp(args[0], "exit") == 0)
    // {
    //     // A função exit geralmente não retorna, mas pode ser projetada para tal
    //     ft_exit(args, ms_data);
    //     exit_code = 0; // Este código pode não ser alcançado
    // }
    // else
    // {
    //     // Se não for um builtin, pode retornar um código específico
    //     // para indicar que um comando externo deve ser tentado.
    //     return (-1); // Exemplo de valor para "não é um builtin"
    // }
    return (exit_code);
}
