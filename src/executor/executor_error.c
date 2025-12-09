/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:04 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:46:57 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_execve_error(char *cmd_name, char **env_array,
				t_minishell *ms_data)
{
	if (errno == EACCES)
		ft_executor_error_eacces(cmd_name);
	else if (errno == EISDIR)
		ft_executor_error_eisdir(cmd_name);
	else if (errno == ENOENT)
		ft_executor_error_eoent(cmd_name);
	else
	{
		ft_print_error(cmd_name, strerror(errno), NULL);
	}
	ft_free_str_arrays(env_array);
	ft_free_shell_child(ms_data);
	if (errno == EACCES || errno == EISDIR)
		_exit(126);
	_exit(127);
}

void	ft_handle_path_not_found(char *cmd_name, char **env_array,
				t_minishell *ms_data)
{
	t_env	*path_var;

	if (errno == EISDIR)
	{
		ft_executor_error_eisdir(cmd_name);
		ft_free_str_arrays(env_array);
		ft_free_shell_child(ms_data);
		_exit(126);
	}
	path_var = ft_get_env_var(ms_data->env_list, "PATH");
	if (ft_strchr(cmd_name, '/') || !path_var || !path_var->value)
		ft_print_error(cmd_name, "No such file or directory", NULL);
	else
		ft_print_error(cmd_name, "command not found", NULL);
	ft_free_str_arrays(env_array);
	ft_free_shell_child(ms_data);
	_exit(127);
}
