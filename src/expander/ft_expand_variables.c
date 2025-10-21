#include "minishell.h"
#include "structs.h"
#include "lexer.h"

int	is_valid_env_var_name(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!( (str[i] >= 'A' && str[i] <= 'Z') || 
			   (str[i] >= 'a' && str[i] <= 'z') || 
			   str[i] == '_' || 
			   (i > 0 && (str[i] >= '0' && str[i] <= '9')) ))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_get_env_value(t_env *env, char *var_name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (current->var && ft_strcmp(current->var, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	ft_expand_variables(t_token *tokens, t_env *env)
{
	t_token	*current;
	char	*var_name;
	char	*env_value;
	char	*new_value;
	char	*old_value;

	current = tokens;
	while (current)
	{
		if (current->value && current->value[0] == '$' && (current->quote == 0 || current->quote == '"'))
		{
			var_name = current->value + 1;
			if (is_valid_env_var_name(var_name))
			{
				env_value = ft_get_env_value(env, var_name);
				/* If variable not found, expand to empty string (bash behavior). */
				if (env_value)
					new_value = ft_strdup(env_value);
				else
					new_value = ft_strdup("");
				if (!new_value)
					return (-1);
				old_value = current->value;
				current->value = new_value;
				free(old_value);
			}
		}
		current = current->next;
	}
	return (0);
}