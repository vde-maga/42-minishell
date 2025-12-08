/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:05 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:29:06 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_helpers.h"
#include "minishell.h"

static void	ft_append_set_value(t_minishell *msdata, char *var_name,
		char *append_val)
{
	t_env	*env;
	char	*new_val;

	env = ft_get_env_var(msdata->env_list, var_name);
	if (env && env->value)
		new_val = ft_strjoin(env->value, append_val);
	else
		new_val = ft_strjoin("", append_val);
	ft_set_env_var(&msdata->env_list, var_name, new_val);
	free(new_val);
}

int	ft_handle_export_append(t_minishell *msdata, char *arg)
{
	char	*plus_equal;
	char	*var_name;
	char	*append_val;

	plus_equal = ft_strnstr(arg, "+=", ft_strlen(arg));
	var_name = ft_substr(arg, 0, plus_equal - arg);
	if (!var_name || !ft_is_valid_identifier(var_name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (free(var_name), 1);
	}
	append_val = ft_remove_quotes(plus_equal + 2);
	ft_append_set_value(msdata, var_name, append_val);
	return (free(var_name), free(append_val), 0);
}

int	ft_calculate_allocate_space(char *value)
{
	int	i;
	int	count_allocate_space;

	i = 0;
	count_allocate_space = 0;
	while (value[i])
	{
		if (value[i] == ' ')
		{
			count_allocate_space++;
			while (value[i] == ' ')
				i++;
		}
		else
		{
			count_allocate_space++;
			i++;
		}
	}
	return (count_allocate_space);
}

char	*ft_remove_spaces(char *value)
{
	int		i;
	int		j;
	char	*new_value;

	new_value = (char *)malloc(ft_calculate_allocate_space(value) + 1);
	if (!new_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		new_value[j++] = value[i];
		if (value[i] == ' ')
			while (value[i] == ' ')
				i++;
		else
			i++;
	}
	new_value[j] = '\0';
	free(value);
	return (new_value);
}
