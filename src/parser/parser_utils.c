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
		/*
			TODO: I think I need to rethink the logic to search by both types.
			In this current implementation: the first type is always considered,
			and the second type is kinda optional.
			I need to search a better way to do this.
		*/
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
	
	// TODO: Parse command logic
	(void)tokens;
	node = ft_parser_new_node(NODE_CMD);
	return (node);
}