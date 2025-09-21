#include "minishell.h"

int ft_exec_replace_cmd_with_path(t_minishell *ms_data, t_cmd_node *cmd)
{
    char *full_path;

    full_path = ft_get_cmd_path(cmd->args[0], ms_data->env);
    if (full_path)
    {
        free(cmd->args[0]);
        cmd->args[0] = full_path;
        return (1);
    }
    free(full_path);
    return (0);
}

void    ft_executor(t_minishell *ms_data, t_parser_node *parser)
{
    int     result;
    t_parser_node   *current;

    // Just print to testings
    current = parser;
    if (current->type == NODE_CMD)
    {
        int i = -1;
        (void)i;
        (void)result;
        // result = ft_exec_replace_cmd_with_path(ms_data,current->cmd_data);
        // if (result)
        // {
        //     ft_printf("[");
        //     while (current->cmd_data->args[++i])
        //         ft_printf("\"%s\", ", current->cmd_data->args[i]);
        //     ft_printf("]\n");
        // }
        // else
        //     ft_printf("minishell: command \"%s\" not found\n", current->cmd_data->args[0]);
        ft_exec_cmd_node(ms_data, current->cmd_data);
    }
}