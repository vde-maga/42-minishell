/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:27:25 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:27:26 by ruiferna         ###   ########.fr       */
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