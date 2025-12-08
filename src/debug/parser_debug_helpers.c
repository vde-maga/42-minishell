/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:45 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:29:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_debug_helpers.h"

void	print_indentation(int level)
{
	int	i;

	i = 0;
	while (i < level)
	{
		ft_printf("  ");
		i++;
	}
}

void	print_cmd_args(t_cmd_node *cmd, int level)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		print_indentation(level + 1);
		ft_printf("arg[%d]: %s\n", i, cmd->args[i]);
		i++;
	}
}

void	print_cmd_redirs(t_cmd_node *cmd, int level)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		print_indentation(level + 1);
		ft_printf("redir: type=%d file=%s\n", r->type, r->filename);
		r = r->next;
	}
}

void	print_cmd_node(t_cmd_node *cmd, int level)
{
	if (!cmd)
		return ;
	print_indentation(level);
	ft_printf("CMD\n");
	if (cmd->args)
		print_cmd_args(cmd, level);
	if (cmd->redirs)
		print_cmd_redirs(cmd, level);
}

void	print_binary_node(t_parser_node *node, int level, char *type_str)
{
	print_indentation(level);
	ft_printf("%s\n", type_str);
	print_parser_node(node->left, level + 1);
	print_parser_node(node->right, level + 1);
}
