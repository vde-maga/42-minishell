#include "minishell.h"

t_env	*ft_get_env_list(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = ft_env_create_node(envp[i]);
		if (!new_node)
		{
			ft_free_env_list(head);
			ft_putstr_fd("Error: failed to create env node\n", 2);
			return (NULL);
		}
		ft_env_add_back(&head, new_node);
		i++;
	}
	return (head);
}

t_env	*ft_get_env_var(t_env *env_list, char *var_name)
{
	t_env	*current;

	if (!env_list || !var_name)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->var, var_name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
