#include "minishell.h"
#include "structs.h"
#include "lexer.h"

int	ft_expand_variables(t_minishell *msdata, t_env *env)
{
	t_token	*current;
	int		ret_val;
	char	*old_value;
	char	*expanded_value;

	if (!msdata || !env)
		return (-1);
		
	current = msdata->tokens;
	ret_val = 0;
	while (current)
	{
		if (current->value && current->type == TOKEN_WORD)
		{
			if (ft_strchr(current->value, '$'))
			{
				expanded_value = ft_expand_variables_in_string(env, current->value);
				if (expanded_value)
				{
					old_value = current->value;
					current->value = expanded_value;
					free(old_value);
				}
				else
				{
					// Expansion failed, return error
					return (-1);
				}
			}
			// Remove quotes after variable expansion
			char *unquoted_value = ft_remove_quotes(current->value);
			if (unquoted_value)
			{
				old_value = current->value;
				current->value = unquoted_value;
				free(old_value);
			}
			else
			{
				// Quote removal failed, return error
				return (-1);
			}
		}
		current = current->next;
	}
	return (ret_val);
}
