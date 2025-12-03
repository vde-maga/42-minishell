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

static char	*ft_readline_append(char *line, char c)
{
	char	*new_line;
	size_t	len;

	if (!line)
	{
		new_line = malloc(2);
		if (!new_line)
			return (NULL);
		new_line[0] = c;
		new_line[1] = '\0';
		return (new_line);
	}
	len = ft_strlen(line);
	new_line = malloc(len + 2);
	if (!new_line)
		return (free(line), NULL);
	ft_memcpy(new_line, line, len);
	new_line[len] = c;
	new_line[len + 1] = '\0';
	free(line);
	return (new_line);
}

char	*ft_heredoc_readline(int fd)
{
	char	*line;
	char	c;
	ssize_t	bytes_read;

	line = NULL;
	while (1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				return (free(line), NULL);
			return (line);
		}
		if (c == '\n')
		{
			line = ft_readline_append(line, c);
			return (line);
		}
		line = ft_readline_append(line, c);
		if (!line)
			return (NULL);
	}
}
