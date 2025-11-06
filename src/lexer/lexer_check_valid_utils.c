#include "../includes/minishell.h"

int	ft_is_operator(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_OR || type == TOKEN_AND
		|| type == TOKEN_AND_IF);
}

int	ft_is_redirect(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

t_token	*ft_check_operator_validity(t_token *current)
{
	if (!current->next)
		return (current);
	if (ft_is_operator(current->next->type))
		return (current->next);
	if (current->next->type == TOKEN_EOF)
		return (current);
	return (NULL);
}

t_token	*ft_check_redirect_validity(t_token *current)
{
	if (!current->next)
		return (current);
	if (current->next->type != TOKEN_WORD)
		return (current->next);
	return (NULL);
}
