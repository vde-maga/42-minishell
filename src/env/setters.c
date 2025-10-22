#include "minishell.h"

void	ft_env_add_back(t_env **lst, t_env *new_node)
{
	t_env	*last;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

int	ft_update_env_var(t_env *env_list, char *var_name, char *new_value)
{
	t_env	*var_node;
	char	*temp;

	if (!env_list || !var_name || !new_value)
		return (1);
	var_node = ft_get_env_var(env_list, var_name);
	if (!var_node)
		return (1);
	temp = ft_strdup(new_value);
	if (!temp)
		return (1);
	free(var_node->value);
	var_node->value = temp;
	return (0);
}
