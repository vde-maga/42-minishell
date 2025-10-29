#include "minishell.h"

t_token *ft_parser_find_last_operator(t_token *tokens,
	t_token_type type1, t_token_type type2)
{
	t_token	*last_operator;
	t_token	*current;

	last_operator = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == type1
			|| (type2 != (t_token_type) -1 && current->type == type2))
			last_operator = current;
		current = current->next;
	}
	return (last_operator);
}

t_parser_node	*ft_parse_command(t_token *tokens)
{
	t_parser_node	*node;
	t_cmd_node		*cmd_data;
	t_token			*current;
	int				i;
	int				args_counter;
	
	node = ft_parser_new_node(NODE_CMD);
	cmd_data = ft_calloc(1, sizeof(t_cmd_node));
	if (!cmd_data)
		return (free(node), NULL);
	node->cmd_data = cmd_data;
	args_counter = ft_parser_count_args(tokens);
	if (args_counter > 0)
	{
		cmd_data->args = ft_calloc(args_counter + 1, sizeof(char *));
		current = tokens;
		i = 0;
		while (current)
		{
			/*
			If the current token is <, >, <<, >> the code adds the redirect (because the next token is surely a filename)
			Because of that, just skips the next token.
			*/
			if (current->type >= TOKEN_REDIRECT_IN && current->type <= TOKEN_HEREDOC)
			{
				ft_parser_add_redirect(cmd_data, current);
				if (current->next)
					current = current->next->next;
				else
					break;
			}
			else if (current->type == TOKEN_WORD)
			{
				if (cmd_data->args && (current->value && current->value[0] != '\0'))
					cmd_data->args[i++] = ft_strdup(current->value);
				current = current->next;
			}
			else // this else means that its a single command, so, just ignores
				current = current->next;
		}
	}
	return (node);
}
