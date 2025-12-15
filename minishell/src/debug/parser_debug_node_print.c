/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_node_print.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:51 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:36 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_debug_helpers.h"

static void	print_node_cmd(t_parser_node *node, int level)
{
	ft_printf("NODE_CMD\n");
	print_cmd_node(node->cmd_data, level + 1);
}

static void	print_node_pipe(t_parser_node *node, int level)
{
	print_binary_node(node, level, "NODE_PIPE");
}

static void	print_node_and(t_parser_node *node, int level)
{
	print_binary_node(node, level, "NODE_AND");
}

static void	print_node_or(t_parser_node *node, int level)
{
	print_binary_node(node, level, "NODE_OR");
}

void	print_parser_node(t_parser_node *node, int level)
{
	if (!node)
	{
		print_indentation(level);
		ft_printf("(null)\n");
		return ;
	}
	print_indentation(level);
	if (node->type == NODE_CMD)
		print_node_cmd(node, level);
	else if (node->type == NODE_PIPE)
		print_node_pipe(node, level);
	else if (node->type == NODE_AND)
		print_node_and(node, level);
	else if (node->type == NODE_OR)
		print_node_or(node, level);
	else
		ft_printf("NODE_UNKNOWN\n");
}
