#include "../includes/minishell.h"

static t_token	*ft_validate_token(t_token *current)
{
	t_token	*result;

	if (ft_is_operator(current->type))
	{
		result = ft_check_operator_validity(current);
		if (result)
			return (result);
	}
	else if (ft_is_redirect(current->type))
	{
		result = ft_check_redirect_validity(current);
		if (result)
			return (result);
	}
	return (NULL);
}

t_token	*ft_lexer_invalid_token(t_token *tokens)
{
	t_token	*current;
	t_token	*result;

	if (!tokens)
		return (NULL);
	current = tokens;
	if (ft_is_operator(current->type))
		return (current);
	while (current)
	{
		result = ft_validate_token(current);
		if (result)
			return (result);
		current = current->next;
	}
	return (NULL);
}
