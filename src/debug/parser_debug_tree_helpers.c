/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_tree_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:55 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:29:56 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_debug_tree_helpers.h"

void	print_prefix(char *prefix)
{
	if (prefix && *prefix)
		ft_printf("%s", prefix);
}

static void	print_tree_cmd_args(t_cmd_node *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
}

static void	print_tree_cmd_redirs(t_cmd_node *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		ft_printf(" [redir type=%s file=%s]", get_token_type_name(r->type),
			r->filename);
		r = r->next;
	}
}

void	print_cmd_details(t_cmd_node *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		print_tree_cmd_args(cmd);
	if (cmd->redirs)
		print_tree_cmd_redirs(cmd);
}

void	print_node_type(t_parser_node *node)
{
	if (node->type == NODE_CMD)
	{
		ft_printf("CMD: ");
		print_cmd_details(node->cmd_data);
		ft_printf("\n");
	}
	else if (node->type == NODE_PIPE)
		ft_printf("PIPE\n");
	else if (node->type == NODE_AND)
		ft_printf("AND\n");
	else if (node->type == NODE_OR)
		ft_printf("OR\n");
	else if (node->type == NODE_SUBSHELL)
		ft_printf("SUBSHELL\n");
	else
		ft_printf("UNKNOWN\n");
}
