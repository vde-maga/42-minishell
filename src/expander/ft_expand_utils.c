#include "minishell.h"

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

int	is_valid_special_param(char *str)
{
	if (!str || !*str)
		return (0);
	
	if ((str[0] == '?' || str[0] == '$') && str[1] == '\0')
		return (1);
	return (0);
}



char	*ft_expand_variables_in_string(t_env *env, char *str)
{
	char	*result;
	char	*temp;
	int		i, j;
	int		in_single_quote;
	int		in_double_quote;
	char	var_name[256];
	int		var_len;

	if (!str)
		return (NULL);
	
	result = ft_strdup("");
	if (!result)
		return (NULL);
	
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			// Add the quote to result for proper quote handling
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			result = temp;
			i++;
		}
		else if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			// Add the quote to result for proper quote handling
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			result = temp;
			i++;
		}
				else if (str[i] == '\\' && !in_single_quote)
		{
			// Handle escape sequences properly
			i++;
			if (str[i])
			{
				// For any escaped character, preserve it literally
				temp = ft_strjoin_char(result, str[i]);
				free(result);
				result = temp;
				i++;
			}
			else
			{
				// If backslash at end of string, preserve it
				temp = ft_strjoin_char(result, '\\');
				free(result);
				result = temp;
			}
		}
		else if (str[i] == '$' && !in_single_quote)
		{
			// Extract variable name
			var_len = 0;
			j = i + 1;
			
			// Handle $"VAR" pattern - treat as literal string VAR (no expansion)
			if (str[j] == '"' && !in_double_quote)
			{
				// Skip the opening quote and $, treat content as literal
				i += 2; // Skip $ and "
				while (str[i] && str[i] != '"')
				{
					temp = ft_strjoin_char(result, str[i]);
					free(result);
					result = temp;
					i++;
				}
				// Skip the closing quote if present
				if (str[i] == '"')
					i++;
				continue;
			}
			else if (str[j] == '\'' && !in_double_quote)
			{
				i += 2;
				while (str[i] && str[i] != '\'')
				{
					temp = ft_strjoin_char(result, str[i]);
					free(result);
					result = temp;
					i++;
				}
				if (str[i] == '\'')
					i++;
				continue;
			}
			else if (str[j] == '?' || str[j] == '$')
			{
				var_name[var_len++] = str[j++];
			}
			else
			{
				while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
				{
					if (var_len < 255)
						var_name[var_len++] = str[j];
					j++;
				}
			}
			var_name[var_len] = '\0';
			
			// Get variable value
			if (var_len > 0)
			{
				char *var_value = ft_get_variable_value(env, var_name);
				if (var_value)
				{
					temp = ft_strjoin(result, var_value);
					free(result);
					result = temp;
					free(var_value);
				}
				i = j;
			}
			else
			{
				// If no valid variable name after $, treat $ as literal
				temp = ft_strjoin_char(result, str[i]);
				free(result);
				result = temp;
				i++;
			}
		}
		else
		{
			temp = ft_strjoin_char(result, str[i]);
			free(result);
			result = temp;
			i++;
		}
	}
	
	return (result);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		len;
	
	if (!s1)
	{
		result = malloc(2);
		if (result)
		{
			result[0] = c;
			result[1] = '\0';
		}
		return (result);
	}
	
	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	
	ft_strlcpy(result, s1, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	
	return (result);
}
