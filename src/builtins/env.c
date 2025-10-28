#include "minishell.h"

int	ft_builtin_env(t_minishell *msdata)
{
	t_env	*current;

	if (!msdata || !msdata->env_list)
		return (0);
	current = msdata->env_list;
	while (current)
	{
		if (current->has_value)
			ft_printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
