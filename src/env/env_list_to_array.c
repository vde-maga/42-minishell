#include "minishell.h"

static char	*ft_create_env_string(t_env *env_node)
{
	char	*env_string;
	size_t	var_len;
	size_t	value_len;

	var_len = ft_strlen(env_node->var);
	value_len = ft_strlen(env_node->value);
	env_string = malloc(var_len + value_len + 2);
	if (!env_string)
		return (NULL);
	ft_strlcpy(env_string, env_node->var, var_len + 1);
	env_string[var_len] = '=';
	ft_strlcpy(env_string + var_len + 1, env_node->value, value_len + 1);
	return (env_string);
}

char	**ft_env_list_to_array(t_env *env_list)
{
	char	**env_array;
	t_env	*current;
	int		count;
	int		i;

	count = ft_env_count_vars(env_list);
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i] = ft_create_env_string(current);
		if (!env_array[i])
		{
			while (--i >= 0)
				free(env_array[i]);
			return (free(env_array), NULL);
		}
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
