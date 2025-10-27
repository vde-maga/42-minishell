#include "minishell.h"

char	*ft_get_var_value(t_minishell *ms_data, char *var_name, int len)
{
	t_env	*env_node;
	char	*var_name_copy;
	char	*result;

	if (len == 1 && var_name[0] == '?')
		return (ft_itoa(ft_exit_code(-1)));
	if (len == 1 && var_name[0] == '$')
		return (ft_itoa(get_shell_pid_from_proc()));
	var_name_copy = ft_substr(var_name, 0, len);
	if (!var_name_copy)
		return (ft_strdup(""));
	env_node = ft_get_env_var(ms_data->env_list, var_name_copy);
	free(var_name_copy);
	if (env_node && env_node->value)
		result = ft_strdup(env_node->value);
	else
		result = ft_strdup("");
	return (result);
}

int	ft_get_var_name_len(char *str)
{
	int	i;

	if (str[0] == '?' || str[0] == '$')
		return (1);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int	ft_is_var_char(char c, char next_c)
{
	if (c != '$' || !next_c)
		return (0);
	if (ft_isalnum(next_c) || next_c == '_'
		|| next_c == '?' || next_c == '$')
		return (1);
	return (0);
}

char	*ft_append_var(t_minishell *ms_data, char *result,
	char *line, int *i)
{
	char	*var_value;
	char	*temp;
	int		var_len;

	var_len = ft_get_var_name_len(&line[*i + 1]);
	var_value = ft_get_var_value(ms_data, &line[*i + 1], var_len);
	temp = result;
	result = ft_strjoin(result, var_value);
	free(temp);
	free(var_value);
	*i += var_len + 1;
	return (result);
}

char	*ft_append_char(char *result, char c)
{
	char	char_str[2];
	char	*temp;

	char_str[0] = c;
	char_str[1] = '\0';
	temp = result;
	result = ft_strjoin(result, char_str);
	free(temp);
	return (result);
}
