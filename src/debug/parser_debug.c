/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:07 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:30:08 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_debug_helpers.h"

void	ft_parser_test(t_token *tokens)
{
	t_parser_node	*root;

	if (!tokens)
	{
		ft_printf("No tokens provided to parser test.\n");
		return ;
	}
	root = ft_parser(tokens);
	ft_printf("--- Parser AST ---\n");
	print_parser_node(root, 0);
	ft_printf("--- End AST ---\n");
	ft_parser_free(root);
}
