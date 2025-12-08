/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:56 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:28:57 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_UTILS_H
# define EXIT_UTILS_H

# include "minishell.h"

char	*ft_remove_quotes_from_arg(char *arg);
int		ft_check_if_numeric(char *str);
int		ft_is_properly_quoted(char *arg);
int		ft_count_args(char **args);
int		ft_is_numeric(char *str);
void	ft_exit_free_and_exit(t_minishell *msdata, int exit_code);

#endif