/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:37:39 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:37:40 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_fallback_to_home(t_minishell *ms_data, char *buffer, size_t size)
{
	t_env	*home;

	home = ft_get_env_var(ms_data->env_list, "HOME");
	if (home && home->value && chdir(home->value) == 0)
	{
		ft_strlcpy(buffer, home->value, size);
		ft_update_env_var(ms_data->env_list, "PWD", home->value);
	}
	else
	{
		ft_strlcpy(buffer, "/", size);
		chdir("/");
		ft_update_env_var(ms_data->env_list, "PWD", "/");
	}
}

void	ft_get_cwd(t_minishell *ms_data, char *buffer, size_t size)
{
	if (getcwd(buffer, size) == NULL)
	{
		if (ms_data)
			ft_fallback_to_home(ms_data, buffer, size);
		else
		{
			perror("getcwd failed");
			ft_strlcpy(buffer, "???", size);
		}
	}
}
