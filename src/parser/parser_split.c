/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:33 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:34:34 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
 * FUNCTION: create_operator_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates a new parser node based on operator token type
 *
 * PARAMETERS
 *   @op: Operator token to create node for
 *
 * RETURN VALUE
 *   Pointer to new operator node, or NULL on allocation failure
 *
 * NOTES
 *   - Maps TOKEN_AND_IF to NODE_AND
 *   - Maps TOKEN_OR to NODE_OR
 *   - Maps TOKEN_PIPE to NODE_PIPE
 *   - Memory must be freed by caller
 * ─────────────────────────────────────────────────────────────────────────
 */
static t_parser_node	*create_operator_node(t_token *op)
{
	t_parser_node	*node;

	if (op->type == TOKEN_AND_IF)
		node = ft_parser_new_node(NODE_AND);
	else if (op->type == TOKEN_OR)
		node = ft_parser_new_node(NODE_OR);
	else
		node = ft_parser_new_node(NODE_PIPE);
	return (node);
}

/*
 * FUNCTION: build_left_branch
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Builds the left subtree of an operator node
 *
 * PARAMETERS
 *   @node: Operator node to set left child for
 *   @tokens: Token list for left side
 *   @op: Operator token (for chain restoration)
 *   @prev: Token before operator (for chain breaking)
 *
 * RETURN VALUE
 *   1 on success, 0 on failure
 *
 * NOTES
 *   - Temporarily breaks token chain at operator position
 *   - Recursively parses left side as separate subtree
 *   - Restores token chain on failure
 *   - Handles memory cleanup on failure path
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	build_left_branch(t_parser_node *node, t_token *tokens,
		t_token *op, t_token *prev)
{
	if (prev)
		prev->next = NULL;
	node->left = ft_parser_build_node_tree(tokens);
	if (!node->left)
	{
		if (prev)
			prev->next = op;
		return (0);
	}
	return (1);
}

/*
 * FUNCTION: build_right_branch
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Builds the right subtree of an operator node
 *
 * PARAMETERS
 *   @node: Operator node to set right child for
 *   @op_next: Token after operator (start of right side)
 *
 * RETURN VALUE
 *   1 on success, 0 on failure
 *
 * NOTES
 *   - Recursively parses right side as separate subtree
 *   - Cleans up left subtree on failure to prevent memory leaks
 *   - Right side starts from token after operator
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	build_right_branch(t_parser_node *node, t_token *op_next)
{
	node->right = ft_parser_build_node_tree(op_next);
	if (!node->right)
	{
		ft_parser_free(node->left);
		return (0);
	}
	return (1);
}

/*
 * FUNCTION: ft_parser_split_and_build
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates a new node for an operator and builds its left and right branches
 *
 * PARAMETERS
 *   @tokens: Complete token list to be split
 *   @op: Operator token to split at
 *
 * RETURN VALUE
 *   Pointer to new operator node with parsed subtrees, or NULL on failure
 *
 * NOTES
 *   - Splits token list at operator position
 *   - Recursively parses left and right sides as separate subtrees
 *   - Restores original token chain after parsing
 *   - Handles memory cleanup on failure
 * ─────────────────────────────────────────────────────────────────────────
 */
t_parser_node	*ft_parser_split_and_build(t_token *tokens, t_token *op)
{
	t_parser_node	*node;
	t_token			*prev;
	t_token			*op_next;

	node = create_operator_node(op);
	if (!node)
		return (NULL);
	prev = ft_get_token_before(tokens, op);
	op_next = op->next;
	if (!build_left_branch(node, tokens, op, prev))
	{
		ft_parser_free(node);
		return (NULL);
	}
	if (!build_right_branch(node, op_next))
	{
		if (prev)
			prev->next = op;
		ft_parser_free(node);
		return (NULL);
	}
	if (prev)
		prev->next = op;
	return (node);
}
