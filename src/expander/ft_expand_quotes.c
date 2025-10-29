#include "minishell.h"

char	*ft_remove_quotes(char *str)
{
	char	*dest;
	char	*result;
	int		i, j;
	int		length;
	int		in_single_quote;
	int		in_double_quote;

	if (!str)
		return (NULL);
	length = ft_strlen(str);
	if (length < 2)
		return (ft_strdup(str));
	
	// Always use the complex case to handle all quote scenarios properly
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (!dest)
		return (NULL);
	
	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
		}
		else if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
		}
		else
		{
			dest[j++] = str[i];
			i++;
		}
	}
	dest[j] = '\0';
	
	// If no quotes were removed, free dest and return a duplicate
	if (j == length)
	{
		free(dest);
		result = ft_strdup(str);
		return (result);
	}
	
	// If quotes were removed, we might have allocated more memory than needed
	// Reallocate to the exact size to avoid wasting memory
	result = ft_strdup(dest);
	free(dest);
	return (result);
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
	(void) msdata;

		if (ft_strcmp(current->value, "$$") == 0)
			new_value = ft_itoa(get_shell_pid_from_proc());
		else if (ft_strcmp(current->value, "$?") == 0)
			new_value = ft_itoa(ft_exit_code(-1));
	else
		new_value = ft_itoa(42);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}
