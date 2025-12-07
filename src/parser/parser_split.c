#include "minishell.h"
#include "parser.h"

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
 * Creates a new node for an operator and builds its left and right branches.
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
		ft_parser_free(node);
		return (NULL);
	}
	if (prev)
		prev->next = op;
	return (node);
}
