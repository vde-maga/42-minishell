/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:03 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:13 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_HELPERS_H
# define EXPORT_HELPERS_H

# include "minishell.h"

int		ft_is_valid_identifier(char *str);
void	ft_env_bubble_sort(t_env **env_array, int count);
void	ft_print_env_var(t_env *env_var);
int		ft_print_env_list(t_minishell *msdata);
int		ft_calculate_allocate_space(char *value);
char	*ft_remove_spaces(char *value);
int		ft_handle_export_append(t_minishell *msdata, char *arg);

#endif
