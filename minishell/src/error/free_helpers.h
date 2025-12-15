/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:53 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:46:46 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_HELPERS_H
# define FREE_HELPERS_H

# include "minishell.h"

void	ft_free_str_arrays(char **str);
void	ft_free_shell_data(t_minishell *ms_data);
void	ft_close_shell_fds(t_minishell *ms_data);
void	ft_free_child_resources(t_minishell *ms_data);

#endif
