#include "minishell.h"

t_token	*ft_expander(t_token *tokens, t_env *env)
{
	if (!tokens)
		return (NULL);

	if (ft_expand_quotes(tokens) == -1)
		return (NULL);

	if (ft_expand_variables(tokens, env) == -1)
		return (NULL);

	return (tokens);
}

