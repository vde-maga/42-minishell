#include "minishell.h"
#include "export_helpers.h"

static int	ft_handle_export_no_equal(t_minishell *msdata, char *arg)
{
	if (!ft_is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (ft_set_env_var(&msdata->env_list, arg, NULL));
}

static int	ft_handle_export_with_equal(t_minishell *msdata, char *arg)
{
	char	*equal_sign;
	char	*var_name;
	char	*value;
	int		result;

	equal_sign = ft_strchr(arg, '=');
	var_name = ft_substr(arg, 0, equal_sign - arg);
	if (!var_name)
		return (1);
	if (!ft_is_valid_identifier(var_name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(var_name);
		return (1);
	}
	value = ft_remove_quotes(equal_sign + 1);
	result = ft_set_env_var(&msdata->env_list, var_name, value);
	free(value);
	free(var_name);
	return (result);
}

int	ft_builtin_export(t_minishell *msdata, char *arg)
{
	if (!msdata)
		return (1);
	if (!arg || !*arg)
		return (ft_print_env_list(msdata));
	if (arg[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...] or export -p\n", 2);
		return (2);
	}
	if (!ft_strchr(arg, '='))
		return (ft_handle_export_no_equal(msdata, arg));
	return (ft_handle_export_with_equal(msdata, arg));
}
