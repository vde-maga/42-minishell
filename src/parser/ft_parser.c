#include "parser.h"

/*
 * Entry point for the parser
 */
t_parser_node	*ft_parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (ft_parser_build_node_tree(tokens));
}

/*
 * Builds the abstract syntax tree recursively.
 */
t_parser_node	*ft_parser_build_node_tree(t_token *tokens)
{
	t_parser_node	*node;
	t_token			*op;

	op = ft_parser_find_last_operator(tokens, TOKEN_AND_IF, TOKEN_OR);
	if (!op)
		op = ft_parser_find_last_operator(tokens, TOKEN_PIPE, -1);
	if (op)
		node = ft_parser_split_and_build(tokens, op);
	else
		node = ft_parse_command(tokens);
	return (node);
}

/*
 * Creates a new node for an operator and builds its left and right branches.
 */
t_parser_node	*ft_parser_split_and_build(t_token *tokens, t_token *op)
{
	t_parser_node	*node;
	t_token			*prev;
	t_token			*op_next;

	if (op->type == TOKEN_AND_IF)
		node = ft_parser_new_node(NODE_AND);
	else if (op->type == TOKEN_OR)
		node = ft_parser_new_node(NODE_OR);
	else
		node = ft_parser_new_node(NODE_PIPE);
	if (!node)
		return (NULL); // TODO: Proper error handling/freeing
	prev = ft_get_token_before(tokens, op);
	op_next = op->next;
	prev->next = NULL;
	node->left = ft_parser_build_node_tree(tokens);
	node->right = ft_parser_build_node_tree(op_next);
	prev->next = op;
	return (node);
}

/*
 * Finds the token immediately preceding a target token in a list.
 */
t_token	*ft_get_token_before(t_token *tokens, t_token *target)
{
	t_token	*current;

	current = tokens;
	while (current && current->next != target)
		current = current->next;
	return (current);
}

/*
 * Finds the last occurrence of specified operator types in the token list.
 */
t_token	*ft_parser_find_last_operator(t_token *tokens, t_token_type type1,
		t_token_type type2)
{
	t_token	*last_operator;
	t_token	*current;

	last_operator = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == type1 || (type2 != (t_token_type) - 1
				&& current->type == type2))
			last_operator = current;
		current = current->next;
	}
	return (last_operator);
}
