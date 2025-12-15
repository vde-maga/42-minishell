/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:27:54 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:43:51 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

// Unified error printing function
void	ft_print_error(char *cmd_name, char *error_msg, char *additional);

// Specialized error functions
void	ft_executor_error_eacces(char *cmd_name);
void	ft_executor_error_eisdir(char *cmd_name);
void	ft_executor_error_eoent(char *cmd_name);
void	ft_print_syntax_error(char *token_value);

#endif
