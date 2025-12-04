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
	
	// Check for parentheses validation first
	if (ft_lexer_valid(tokens) == -1)
	{
		// Find the specific invalid token
		current = tokens;
		if (ft_is_operator(current->type) || current->type == TOKEN_RPAREN)
			return (current);
		while (current)
		{
			if (current->type == TOKEN_LPAREN && current->next &&
				current->next->type == TOKEN_RPAREN)
				return (current);
			current = current->next;
		}
		return (tokens); // Return first token if specific error not found
	}
	
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
