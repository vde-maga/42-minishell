/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:22 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:48:39 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
 * FUNCTION: ft_parser
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Entry point for the parser that converts token list to AST
 *
 * PARAMETERS
 *   @tokens: Linked list of tokens to be parsed
 *
 * RETURN VALUE
 *   Pointer to root of AST tree, or NULL if tokens is NULL or parsing fails
 *
 * NOTES
 *   - Validates input tokens before processing
 *   - Delegates actual tree construction to ft_parser_build_node_tree
 * ─────────────────────────────────────────────────────────────────────────
 */
t_parser_node	*ft_parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (ft_parser_build_node_tree(tokens));
}

/*
 * FUNCTION: ft_parser_build_node_tree
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Recursively builds the abstract syntax tree from tokens following
 *   operator precedence rules
 *
 * PARAMETERS
 *   @tokens: Linked list of tokens to be converted to AST nodes
 *
 * RETURN VALUE
 *   Pointer to root of constructed AST subtree, or NULL on failure
 *
 * NOTES
 *   - Operator precedence (lowest to highest):
 *     1. && and || (logical operators, left-to-right)
 *     2. | (pipe)
 *     3. Parentheses (grouping)
 *   - Uses recursive descent parsing strategy
 *   - Handles subshell creation for parenthesized expressions
 * ─────────────────────────────────────────────────────────────────────────
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
