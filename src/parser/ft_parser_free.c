#include "parser.h"

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
		free_string_array(cmd_data->args);
	if (cmd_data->redirs)
		free_redir_list(cmd_data->redirs);
	free(cmd_data);
}

// Helper to free a null-terminated array of strings.
void	free_string_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_redir_list(t_redir *list)
{
	t_redir	*current;
	t_redir	*next;

	current = list;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		if (current->heredoc_content)
			free(current->heredoc_content);
		free(current);
		current = next;
	}
}
