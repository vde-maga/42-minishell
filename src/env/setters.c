#include "minishell.h"

static t_env	*ft_create_env_var(char *var_name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var = ft_strdup(var_name);
	if (!new_node->var)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		free(new_node->var);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

int	ft_set_env_var(t_env **env_list, char *var_name, char *value)
{
	t_env	*var_node;
	t_env	*new_node;

	if (!env_list || !var_name || !value)
		return (1);
	var_node = ft_get_env_var(*env_list, var_name);
	if (var_node)
		return (ft_update_env_var(*env_list, var_name, value));
	new_node = ft_create_env_var(var_name, value);
	if (!new_node)
		return (1);
	ft_env_add_back(env_list, new_node);
	return (0);
}

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

int	ft_unset_env_var(t_env **env_list, char *var_name)
{
	t_env	*previous;
	t_env	*current;

	if (!env_list || !*env_list || !var_name)
		return (1);
	previous = NULL;
	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->var, var_name) == 0)
		{
			if (!previous)
				*env_list = current->next;
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
	return (1);
}
