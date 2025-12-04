#include "parser.h"
#include "minishell.h"

// Recursively frees the entire parser node tree.
void	ft_parser_free(t_parser_node *node)
{
	if (!node)
		return ;
	if (node->left)
		ft_parser_free(node->left);
	if (node->right)
		ft_parser_free(node->right);
	if (node->cmd_data)
		ft_parser_free_cmd_data(node->cmd_data);
	free(node);
}

// Frees the contents of a command node (args, redirections).
void	ft_parser_free_cmd_data(t_cmd_node *cmd_data)
{
	if (!cmd_data)
		return ;
	if (cmd_data->args)
		ft_free_str_arrays(cmd_data->args);
	if (cmd_data->redirs)
		free_redir_list(cmd_data->redirs);
	free(cmd_data);
}


void	free_redir_list(t_redir *list)
{
	if (!list)
		return ;
	ft_free_linked_list(list, ft_free_redir_node);
}
