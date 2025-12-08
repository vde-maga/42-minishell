/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parentheses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:30 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:34:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
 * FUNCTION: ft_restore_chain
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Restores the token chain after temporarily breaking it for parsing
 *
 * PARAMETERS
 *   @before_close: Token that should point to closing parenthesis
 *   @closing_paren: The closing parenthesis token
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Used to maintain token list integrity after subshell parsing
 *   - Handles NULL case safely
 * ─────────────────────────────────────────────────────────────────────────
 */
static void	ft_restore_chain(t_token *before_close, t_token *closing_paren)
{
	if (before_close)
		before_close->next = closing_paren;
}

/*
 * FUNCTION: find_matching_paren
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Finds the matching closing parenthesis for an opening parenthesis
 *
 * PARAMETERS
 *   @tokens: Token list starting with TOKEN_LPAREN
 *
 * RETURN VALUE
 *   Pointer to matching TOKEN_RPAREN, or NULL if not found
 *
 * NOTES
 *   - Handles nested parentheses correctly
 *   - Returns NULL for mismatched parentheses
 *   - Uses paren counting to track nesting level
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: build_subshell_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates a subshell node and parses the content inside parentheses
 *
 * PARAMETERS
 *   @content_start: First token inside parentheses
 *   @before_close: Token before closing parenthesis
 *   @closing_paren: The closing parenthesis token
 *
 * RETURN VALUE
 *   Pointer to subshell node, or NULL on failure
 *
 * NOTES
 *   - Creates NODE_SUBSHELL type parser node
 *   - Recursively parses content as left child
 *   - Restores token chain on failure using comma operator
 *   - Memory cleanup handled on failure path
 * ─────────────────────────────────────────────────────────────────────────
 */
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
 * FUNCTION: ft_parser_handle_parentheses
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handles parentheses by finding matching closing parenthesis and
 *   parsing content inside as a subshell
 *
 * PARAMETERS
 *   @tokens: Token list starting with TOKEN_LPAREN
 *
 * RETURN VALUE
 *   Pointer to subshell node, or NULL on failure
 *
 * NOTES
 *   - Temporarily breaks token chain to isolate subshell content
 *   - Restores original token chain after parsing
 *   - Creates NODE_SUBSHELL type with parsed content as left child
 *   - Handles mismatched parentheses gracefully
 * ─────────────────────────────────────────────────────────────────────────
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
