#include "minishell.h"

int	ft_builtin_env(t_minishell *msdata)
{
	t_env	*current;

	// TODO: Check the need to make it in a alphabetical order
	current = msdata->env_list;
	while(current)
	{
		ft_printf("%s=%s\n", current->var, current->value);
		current=current->next;
	}
	return (0);
}