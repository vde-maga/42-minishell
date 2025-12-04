#include "parser.h"
#include "minishell.h"

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
		return (NULL);
	prev = ft_get_token_before(tokens, op);
	op_next = op->next;
	if (prev)
		prev->next = NULL;
	node->left = ft_parser_build_node_tree(tokens);
	if (!node->left)
	{
		if (prev)
			prev->next = op;
		ft_parser_free(node);
		return (NULL);
	}
	node->right = ft_parser_build_node_tree(op_next);
	if (!node->right)
	{
		if (prev)
			prev->next = op;
		ft_parser_free(node->left);
		ft_parser_free(node);
		return (NULL);
	}
	if (prev)
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

/*
** Helper to restore token chain (avoids duplication in error paths)
*/
static void	ft_restore_chain(t_token *before_close, t_token *closing_paren)
{
	if (before_close)
		before_close->next = closing_paren;
}

/*
** Handles parentheses by finding matching closing parenthesis and
** parsing the content inside as a subshell.
*/
t_parser_node	*ft_parser_handle_parentheses(t_token *tokens)
{
	t_parser_node	*node;
	t_token			*content_start;
	t_token			*closing_paren;
	t_token			*before_close;
	int				paren_count;

	if (!tokens || tokens->type != TOKEN_LPAREN)
		return (NULL);
	content_start = tokens->next;
	closing_paren = content_start;
	paren_count = 1;
	while (closing_paren && paren_count > 0)
	{
		if (closing_paren->type == TOKEN_LPAREN)
			paren_count++;
		else if (closing_paren->type == TOKEN_RPAREN)
			paren_count--;
		if (paren_count > 0)
			closing_paren = closing_paren->next;
	}
	if (paren_count != 0 || !closing_paren)
		return (NULL);
	before_close = ft_get_token_before(content_start, closing_paren);
	if (before_close)
		before_close->next = NULL;
	node = ft_parser_new_node(NODE_SUBSHELL);
	if (!node)
		return (ft_restore_chain(before_close, closing_paren), NULL);
	node->left = ft_parser_build_node_tree(content_start);
	if (!node->left)
	{
		ft_parser_free(node);
		return (ft_restore_chain(before_close, closing_paren), NULL);
	}
	if (before_close)
		before_close->next = closing_paren;
	return (node);
}

/*
	* Finds the last occurrence of specified operator types outside of parentheses.
	*/
t_token	*ft_parser_find_last_operator_paren(t_token *tokens, t_token_type type1,
		t_token_type type2)
{
	t_token	*last_operator;
	t_token	*current;
	int		paren_count;

	last_operator = NULL;
	current = tokens;
	paren_count = 0;
	
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			paren_count++;
		else if (current->type == TOKEN_RPAREN)
			paren_count--;
		else if (paren_count == 0 && (current->type == type1 ||
			(type2 != (t_token_type) - 1 && current->type == type2)))
			last_operator = current;
		current = current->next;
	}
	return (last_operator);
}
