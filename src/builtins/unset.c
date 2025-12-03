#include "minishell.h"

static int	is_valid_identifier(char *str)
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

int	ft_builtin_unset(t_minishell *msdata, char **args)
{
	int	i;

	if (!msdata)
		return (1);
	if (!args || !args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1] != '\0')
	{
		ft_putstr_fd("minishell: unset: -", 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			ft_unset_env_var(&msdata->env_list, args[i]);
		i++;
	}
	return (0);
}
