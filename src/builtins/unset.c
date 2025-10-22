#include "minishell.h"

int	ft_builtin_unset(t_minishell *msdata, char *key)
{
	t_env	*previous;
	t_env	*current;

	previous = NULL;
	current = msdata->env_list;
	while (current)
	{
		// TODO: Do this logic in a specific env function (check if it's better)
		if (ft_strcmp(current->var, key) == 0)
		{
			if (!previous)
				msdata->env_list = current->next;
			else
				previous->next = current->next;
			free(current->var);
			free(current->value);
			free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (-1);
}
