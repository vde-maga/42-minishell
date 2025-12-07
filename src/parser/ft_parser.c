#include "minishell.h"
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
 * Operator precedence (lowest to highest):
 * 1. && and || (logical operators, left-to-right)
 * 2. | (pipe)
 * 3. Parentheses (grouping)
 */
t_parser_node	*ft_parser_build_node_tree(t_token *tokens)
{
	t_parser_node	*node;
	t_token			*op;

	if (!tokens)
		return (NULL);
	op = ft_parser_find_last_operator_paren(tokens, TOKEN_AND_IF, TOKEN_OR);
	if (!op)
		op = ft_parser_find_last_operator_paren(tokens, TOKEN_PIPE, -1);
	if (op)
		node = ft_parser_split_and_build(tokens, op);
	else if (tokens->type == TOKEN_LPAREN)
		node = ft_parser_handle_parentheses(tokens);
	else
		node = ft_parse_command(tokens);
	return (node);
}
