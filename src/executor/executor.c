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

int ft_exec_node(t_minishell *ms_data, t_parser_node *node)
{
    if (!node)
        return (0);
    if (node->type == NODE_CMD)
        return (ft_exec_cmd_node(ms_data, node->cmd_data));
    else if (node->type == NODE_AND)
    {
        ft_exec_node(ms_data, node->left);
        if (ft_exit_code(-1) == 0)
            ft_exec_node(ms_data, node->right);
        return ft_exit_code(-1);
    }
    else if (node->type == NODE_OR)
    {
        ft_exec_node(ms_data, node->left);
        if (ft_exit_code(-1) != 0)
            ft_exec_node(ms_data, node->right);
        return ft_exit_code(-1);
    }
    else if (node->type == NODE_PIPE)
        return (ft_exec_pipe_node(ms_data, node));
    return (0);
}

void    ft_executor(t_minishell *ms_data, t_parser_node *parser)
{
    if (!parser)
    {
        ft_printf("executor: parser (null)");
        return ;
    }

    ft_exec_node(ms_data, parser);
}