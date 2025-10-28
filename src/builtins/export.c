#include "minishell.h"

static int	ft_is_valid_identifier(char *str)
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

static void	ft_env_bubble_sort(t_env **env_array, int count)
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

static int	ft_print_env_list(t_minishell *msdata)
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
		if (env_array[i]->has_value)
			ft_printf("declare -x %s=\"%s\"\n", env_array[i]->var, env_array[i]->value);
		else
			ft_printf("declare -x %s\n", env_array[i]->var);
		i++;
	}
	free(env_array);
	return (0);
}

int	ft_builtin_export(t_minishell *msdata, char *arg)
{
	char	*equal_sign;
	char	*var_name;
	char	*value;
	int		result;

	if (!msdata)
		return (1);
	if (!arg || !*arg)
		return (ft_print_env_list(msdata));
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		if (!ft_is_valid_identifier(arg))
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			return (1);
		}
		return (ft_set_env_var(&msdata->env_list, arg, NULL));
	}
	var_name = ft_substr(arg, 0, equal_sign - arg);
	if (!var_name)
		return (1);
	if (!ft_is_valid_identifier(var_name))
		return (ft_putstr_fd("minishell: export: not a valid identifier\n",2),
		free(var_name), 1);
	value = ft_remove_quotes(equal_sign + 1);
	result = ft_set_env_var(&msdata->env_list, var_name, value);
	return (free(var_name), result);
}
