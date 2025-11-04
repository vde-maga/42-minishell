#include "minishell.h"

t_token	*ft_expander(t_minishell *msdata, t_env *env)
{
	if (!msdata->tokens)
		return (NULL);
	if (ft_expand_variables(msdata, env) == -1)
		return (NULL);
	return (msdata->tokens);
}
