#include "parser.h"
#include "minishell.h"

/*
 *  Parses a simple command (no pipes or other operators).
 */
t_parser_node	*ft_parse_command(t_token *tokens)
{
	t_parser_node	*node;
	t_cmd_node		*cmd_data;

	if (!tokens)
		return (NULL);
	node = ft_parser_new_node(NODE_CMD);
	if (!node)
		return (NULL);
	cmd_data = ft_calloc(1, sizeof(t_cmd_node));
	if (!cmd_data)
	{
		free(node);
		return (NULL);
	}
	node->cmd_data = cmd_data;
	if (ft_populate_cmd_data(cmd_data, tokens) != 0)
	{
		ft_parser_free(node);
		return (NULL);
	}
	return (node);
}

/*
 * Fills the t_cmd_node with arguments and redirection data.
 */
int	ft_populate_cmd_data(t_cmd_node *cmd, t_token *toks)
{
	if (init_cmd_args(cmd, toks) != 0)
		return (1);
	if (process_token_list(cmd, toks) != 0)
		return (1);
	return (0);
}

/*
 * Handles a single word token: duplicates it and adds to the args array.
 */
int	ft_handle_word_token(t_cmd_node *cmd, int *i, char *value)
{
	if (!cmd->args || !value)
		return (0);
	cmd->args[*i] = ft_strdup(value);
	if (!cmd->args[*i])
	{
		ft_free_str_arrays(cmd->args);
		cmd->args = NULL;
		return (1);
	}
	(*i)++;
	return (0);
}

/*
 * Counts how many WORD tokens are in a list, skipping redirections.
 */
int	ft_parser_count_args(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value)
			count++;
		else if (current->type >= TOKEN_REDIRECT_IN
			&& current->type <= TOKEN_HEREDOC)
		{
			if (current->next)
				current = current->next;
			else
				break ;
		}
		current = current->next;
	}
	return (count);
}

/*
 * Allocates and initializes a new parser node.
 */
t_parser_node	*ft_parser_new_node(t_node_type type)
{
	t_parser_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_parser_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}
