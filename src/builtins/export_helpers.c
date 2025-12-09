/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:01 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:11 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_env_bubble_sort(t_env **env_array, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env_array[i]->var, env_array[j]->var) > 0)
			{
				temp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_env_var(t_env *env_var)
{
	if (ft_strcmp(env_var->var, "_") == 0)
		return ;
	if (env_var->has_value)
		ft_printf("declare -x %s=\"%s\"\n", env_var->var, env_var->value);
	else
		ft_printf("declare -x %s\n", env_var->var);
}

int	ft_print_env_list(t_minishell *msdata)
{
	t_env	**env_array;
	int		count;
	int		i;

	count = ft_env_count_vars(msdata->env_list);
	if (count == 0)
		return (0);
	env_array = ft_env_to_array(msdata->env_list, count);
	if (!env_array)
		return (1);
	ft_env_bubble_sort(env_array, count);
	i = 0;
	while (i < count)
	{
		ft_print_env_var(env_array[i]);
		i++;
	}
	free(env_array);
	return (0);
}
