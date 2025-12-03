#include "minishell.h"

int	ft_builtin_env(t_minishell *msdata, char **args)
{
	t_env	*current;

	if (!msdata || !msdata->env_list)
		return (0);
	if (args && args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	current = msdata->env_list;
	while (current)
	{
		if (current->has_value)
			ft_printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
