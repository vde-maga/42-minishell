#include "../includes/minishell.h"

static int	ft_is_operator(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_OR || type == TOKEN_AND
		|| type == TOKEN_AND_IF);
}

static int	ft_is_redirect(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	ft_check_operator(t_token *token)
{
	if (!token->next)
		return (-1);
	if (ft_is_operator(token->next->type))
		return (-1);
	if (token->next->type == TOKEN_EOF)
		return (-1);
	return (1);
}

static int	ft_check_redirect(t_token *token)
{
	if (!token->next)
		return (-1);
	if (token->next->type != TOKEN_WORD)
		return (-1);
	return (1);
}

int	ft_lexer_valid(t_token *tokens)
{
	t_token	*current;
	int		has_command;

	if (!tokens)
		return (1);
	current = tokens;
	if (ft_is_operator(current->type))
		return (-1);
	if (ft_is_redirect(current->type))
		return (-1);

	has_command = 0;
	while (current)
	{
		if (ft_is_operator(current->type))
		{
			if (ft_check_operator(current) == -1)
				return (-1);
			has_command = 0; // Reset after operator
		}
		else if (ft_is_redirect(current->type))
		{
			if (ft_check_redirect(current) == -1)
				return (-1);
			if (!has_command)
				return (-1); // Redirect without command
		}
		else if (current->type == TOKEN_WORD)
			has_command = 1;
		current = current->next;
	}
	return (1);
}
