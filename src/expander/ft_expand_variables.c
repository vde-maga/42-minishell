#include "minishell.h"
#include "structs.h"
#include "lexer.h"

int	ft_expand_variables(t_minishell *msdata, t_env *env)
{
	t_token	*current;
	char	*var_name;
	int		ret_val;
	char	*old_value;

	current = msdata->tokens;
	ret_val = 0;
	while (current)
	{
		if (current->value && current->value[0] == '$'
				&& (current->quote == 0 || current->quote == '"'))
		{
			var_name = current->value + 1;
			if (is_valid_special_param(var_name))
				ret_val = ft_exp_special_param(msdata, current, var_name);
			else if (is_valid_env_var_name(var_name))
				ret_val = ft_exp_replace_content(env, current, var_name);
			else if (var_name[0] != '\0')
			{
				old_value = current->value;
				current->value = ft_strdup("");
				if (!current->value)
					return (-1);
				free(old_value);
			}
		}
		current = current->next;
	}
	return (ret_val);
}