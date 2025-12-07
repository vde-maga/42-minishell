#include "minishell.h"

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
	var_value = ft_get_variable_value_len(ms_data->env_list,
			&line[*i + 1], var_len);
	temp = result;
	result = ft_strjoin(result, var_value);
	free(temp);
	free(var_value);
	*i += var_len + 1;
	return (result);
}
