/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:13 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:44:14 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_UTILS_H
# define PATH_UTILS_H

# include "minishell.h"

char	*ft_get_variable_value(t_env *env, char *var_name);
char	*ft_get_variable_value_len(t_env *env, char *var_name, int len);
char	*ft_path_tilde_expand(t_env *env, const char *path);
char	*ft_path_tilde_shorten(t_env *env, const char *path);
int		get_shell_pid_from_proc(void);

#endif
