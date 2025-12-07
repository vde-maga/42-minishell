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

static char	*ft_expand_heredoc_line(t_minishell *ms_data, char *line)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (ft_is_var_char(line[i], line[i + 1]))
			result = ft_append_var(ms_data, result, line, &i);
		else
		{
			result = ft_append_char(result, line[i]);
			i++;
		}
	}
	return (result);
}

char	*ft_process_heredoc_line(t_minishell *ms_data, char *line,
	int was_quoted)
{
	char	*expanded;

	if (!was_quoted)
	{
		expanded = ft_expand_heredoc_line(ms_data, line);
		free(line);
		return (expanded);
	}
	return (line);
}
