/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_tree_print.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:00 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:30:01 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_debug_tree_helpers.h"

static void	set_connector(char *connector, int is_left)
{
	if (is_left == 0)
		ft_strlcpy(connector, "", 16);
	else if (is_left == 1)
		ft_strlcpy(connector, "├─ ", 16);
	else
		ft_strlcpy(connector, "└─ ", 16);
}

static void	prepare_prefix(char *new_prefix, char *prefix, int is_left)
{
	if (is_left == 0)
		ft_strlcpy(new_prefix, "", 1024);
	else if (is_left == 1)
	{
		ft_strlcpy(new_prefix, prefix, 1024);
		ft_strlcat(new_prefix, "│  ", 1024);
	}
	else
	{
		ft_strlcpy(new_prefix, prefix, 1024);
		ft_strlcat(new_prefix, "   ", 1024);
	}
}

static void	print_left_child(t_parser_node *node, char *new_prefix)
{
	if (node->left)
		print_parser_tree(node->left, new_prefix, 1);
	else if (node->right)
	{
		print_prefix(new_prefix);
		ft_printf("├─ (null)\n");
	}
}

static void	print_right_child(t_parser_node *node, char *prefix, int is_left)
{
	char	right_prefix[1024];

	if (node->right)
	{
		if (is_left == 0)
			ft_strlcpy(right_prefix, "", 1024);
		else if (is_left == 1)
		{
			ft_strlcpy(right_prefix, prefix, 1024);
			ft_strlcat(right_prefix, "│  ", 1024);
		}
		else
		{
			ft_strlcpy(right_prefix, prefix, 1024);
			ft_strlcat(right_prefix, "   ", 1024);
		}
		print_parser_tree(node->right, right_prefix, 2);
	}
}

void	print_parser_tree(t_parser_node *node, char *prefix, int is_left)
{
	char	new_prefix[1024];
	char	connector[16];

	if (!node)
	{
		print_prefix(prefix);
		ft_printf("(null)\n");
		return ;
	}
	if (prefix == NULL)
		prefix = "";
	set_connector(connector, is_left);
	print_prefix(prefix);
	ft_printf("%s", connector);
	print_node_type(node);
	if (node->left || node->right)
	{
		prepare_prefix(new_prefix, prefix, is_left);
		print_left_child(node, new_prefix);
		print_right_child(node, prefix, is_left);
	}
}
