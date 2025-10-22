#include "minishell.h"

static int	ft_fill_env_node(t_env *node, char *envp_line, char *split_pos)
{
	int	var_len;

	var_len = split_pos - envp_line;
	node->var = malloc(sizeof(char) * (var_len + 1));
	if (!node->var)
		return (1);
	ft_strlcpy(node->var, envp_line, var_len + 1);
	node->value = ft_strdup(split_pos + 1);
	if (!node->value)
	{
		free(node->var);
		return (1);
	}
	return (0);
}

t_env	*ft_env_create_node(char *envp_line)
{
	t_env	*new_node;
	char	*equal_sign_pos;
	int		fill_status;

	equal_sign_pos = ft_strchr(envp_line, '=');
	if (!equal_sign_pos)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	fill_status = ft_fill_env_node(new_node, envp_line, equal_sign_pos);
	if (fill_status == 1)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	**ft_env_to_array(t_env *env_list, int count)
{
	t_env	**env_array;
	t_env	*current;
	int		i;

	env_array = malloc(sizeof(t_env *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		env_array[i] = current;
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

