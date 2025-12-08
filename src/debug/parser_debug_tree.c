/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:03 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:30:04 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_debug_tree_helpers.h"

void	ft_parser_tree_test(t_parser_node *root)
{
	ft_printf("---------- Parser Debugger ------\n");
	print_parser_tree(root, "", 0);
	ft_printf("------- End Parser Debugger -----\n");
}
