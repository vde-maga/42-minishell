/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:27:49 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:43:41 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_FUNCS_H
# define DEBUG_FUNCS_H

// Test / debug helpers functions
void	ft_parser_test(t_token *tokens);
void	ft_parser_tree_test(t_parser_node *root);
void	print_tokens(t_token *tokens);
void	ft_test_heredoc(t_minishell *ms);

// Debug -c flag functions
int		ft_debug_c_flag(t_minishell *ms_data, char *cmd_string);
int		ft_debug_main_with_c_flag(int argc, char **argv, char **envp);

#endif
