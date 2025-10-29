#include "minishell.h"

t_parser_node	*ft_parser_new_node(t_node_type type)
{
	t_parser_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_parser_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

int	ft_parser_count_args(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current)
	{
		if (current->type == TOKEN_WORD 
			&& (current->value && current->value[0] != '\0')) // id 0 / added check to not count empty strings as args
				count++;
		else if (current->type >= TOKEN_REDIRECT_IN
		&& current->type <= TOKEN_HEREDOC) // ids 4 to 7
		{
			if (current->next)
				current = current->next;
			else
				break;
		}
		current = current->next;
	}
	return (count);
}

void	ft_parser_add_redirect(t_cmd_node *cmd_data, t_token *redirect_tok)
{
	t_redir	*new_redirect;
	t_redir	*last;

	if (!redirect_tok->next || redirect_tok->next->type != TOKEN_WORD)
		return ;
	new_redirect = ft_calloc(1, sizeof(t_redir));
	if (!new_redirect)
		return ;
	new_redirect->type = redirect_tok->type;
	new_redirect->filename = ft_strdup(redirect_tok->next->value);
	if (!new_redirect->filename)
	{
		free(new_redirect);
		return ;
	}
	new_redirect->was_quoted = redirect_tok->next->was_quoted;
	if (!cmd_data->redirs)
		cmd_data->redirs = new_redirect;
	else
	{
		last = cmd_data->redirs;
		while (last->next)
			last = last->next;
		last->next=new_redirect;
	}
}

void	ft_parser_free(t_parser_node *node)
{
	if (!node)
		return;
	if (node->left)
		ft_parser_free(node->left);
	if (node->right)
		ft_parser_free(node->right);
	if (node->cmd_data)
	{
		if (node->cmd_data->args)
		{
			int i = 0;
			while (node->cmd_data->args[i])
			{
				free(node->cmd_data->args[i]);
				i++;
			}
			free(node->cmd_data->args);
		}
		t_redir *r = node->cmd_data->redirs;
		while (r)
		{
			t_redir *next = r->next;
			if (r->filename)
				free(r->filename);
			free(r);
			r = next;
		}
		free(node->cmd_data);
	}
	free(node);
}