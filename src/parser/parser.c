#include "minishell.h"

t_parser_node	*ft_parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (ft_parser_build_node_tree(tokens));
}

t_parser_node	*ft_parser_build_node_tree(t_token *tokens)
{
	t_parser_node	*node;
	t_token			*op;
	t_token			*prev;

	op = ft_parser_find_last_operator(tokens, TOKEN_AND_IF, TOKEN_OR);
	if (!op)
		op = ft_parser_find_last_operator(tokens, TOKEN_PIPE, -1);
	if (op)
	{
		if (op->type == TOKEN_AND_IF)
			node = ft_parser_new_node(NODE_AND);
		else if (op->type == TOKEN_OR)
			node = ft_parser_new_node(NODE_OR);
		else
			node = ft_parser_new_node(NODE_PIPE);
		// Now that the last operator is parsed, we can use recursion to populate
		// the remaining branches of the "tree"
		prev = tokens;
		while (prev->next != op)
			prev = prev->next;
		prev->next = NULL;
		node->left = ft_parser_build_node_tree(tokens);
		node->right = ft_parser_build_node_tree(op->next);
		return (node);
	}
	// At this point all operators should be populated on the tree.
	// Now its time to parse the commands (and redirections)
	return(ft_parse_command(tokens));
}