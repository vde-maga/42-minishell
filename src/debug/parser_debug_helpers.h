/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_debug_helpers.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:48 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:34 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_DEBUG_HELPERS_H
# define PARSER_DEBUG_HELPERS_H

# include "minishell.h"

void	print_cmd_args(t_cmd_node *cmd, int level);
void	print_cmd_redirs(t_cmd_node *cmd, int level);
void	print_cmd_node(t_cmd_node *cmd, int level);
void	print_binary_node(t_parser_node *node, int level, char *type_str);
void	print_parser_node(t_parser_node *node, int level);
void	print_indentation(int level);

#endif
