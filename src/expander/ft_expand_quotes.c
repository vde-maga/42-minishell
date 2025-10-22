#include "minishell.h"

char	*ft_remove_quotes(char *str)
{
	char	*dest;
	int		length;

	if (!str)
		return (NULL);
	length = ft_strlen(str);
	if (length < 2)
	{
		dest = ft_strdup(str);
		if (!dest)
			return (NULL);
		return (dest);
	}
	dest = (char *)malloc(sizeof(char) * (length - 2 + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, str + 1, length - 1);
	return (dest);
}

int	ft_expand_quotes(t_token *tokens)
{
	t_token	*current;
	char	*new_value;
	char	*old_value;

	current = tokens;
	while (current)
	{
		if (current->was_quoted == 1)
		{
			new_value = ft_remove_quotes(current->value);
			if (!new_value)
				return (-1);
			old_value = current->value;
			current->value = new_value;
			free(old_value);
		}
		current = current->next;
	}
	return (0);
}

int	ft_exp_replace_content(t_env *env, t_token *current, char *var_name)
{
	char	*new_value;
	char	*old_value;
	t_env	*env_node;

	env_node = ft_get_env_var(env, var_name);
	if (env_node && env_node->value)
		new_value = ft_strdup(env_node->value);
	else
		new_value = ft_strdup("");
	if (!new_value)
		return (-1);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}

int	ft_exp_special_param(t_minishell *msdata, t_token *current, char *var_name)
{
	char	*new_value;
	char	*old_value;
	(void) var_name;

	if (ft_strcmp(current->value, "$$") == 0)
		new_value = ft_itoa(get_shell_pid_from_proc());
	else if (ft_strcmp(current->value, "$?") == 0)
		new_value = ft_itoa(msdata->exit_status);
	else
		new_value = ft_itoa(42);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}
