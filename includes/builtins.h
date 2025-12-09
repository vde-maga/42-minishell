/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:27:25 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:43:32 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_builtin_pwd(void);
int	ft_builtin_cd(t_minishell *data, char **args);
int	ft_builtin_echo(char **args);
int	ft_builtin_unset(t_minishell *msdata, char **args);
int	ft_builtin_env(t_minishell *msdata, char **args);
int	ft_builtin_export(t_minishell *msdata, char **args);
int	ft_builtin_exit(t_minishell *msdata, char **args);

#endif
