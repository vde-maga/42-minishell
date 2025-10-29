#include "minishell.h"
#include "structs.h"
#include "lexer.h"

int	ft_expand_variables(t_minishell *msdata, t_env *env)
{
	t_token	*current;
	int		ret_val;
	char	*old_value;
	char	*expanded_value;

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
			}
		}
		current = current->next;
	}
	return (ret_val);
}