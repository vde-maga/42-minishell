#include "minishell.h"
#include "parser.h"

static void	ft_restore_chain(t_token *before_close, t_token *closing_paren)
{
	if (before_close)
		before_close->next = closing_paren;
}

static t_token	*find_matching_paren(t_token *tokens)
{
	t_token	*closing_paren;
	int		paren_count;

	closing_paren = tokens->next;
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
	return (closing_paren);
}

static t_parser_node	*build_subshell_node(t_token *content_start,
		t_token *before_close, t_token *closing_paren)
{
	t_parser_node	*node;

	node = ft_parser_new_node(NODE_SUBSHELL);
	if (!node)
		return (ft_restore_chain(before_close, closing_paren), NULL);
	node->left = ft_parser_build_node_tree(content_start);
	if (!node->left)
	{
		ft_parser_free(node);
		return (ft_restore_chain(before_close, closing_paren), NULL);
	}
	return (node);
}

/*
 * Handles parentheses by finding matching closing parenthesis and
 * parsing content inside as a subshell.
 */
t_parser_node	*ft_parser_handle_parentheses(t_token *tokens)
{
	t_parser_node	*node;
	t_token			*content_start;
	t_token			*closing_paren;
	t_token			*before_close;

	if (!tokens || tokens->type != TOKEN_LPAREN)
		return (NULL);
	content_start = tokens->next;
	closing_paren = find_matching_paren(tokens);
	if (!closing_paren)
		return (NULL);
	before_close = ft_get_token_before(content_start, closing_paren);
	if (before_close)
		before_close->next = NULL;
	node = build_subshell_node(content_start, before_close, closing_paren);
	if (before_close)
		before_close->next = closing_paren;
	return (node);
}
