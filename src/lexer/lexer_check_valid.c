#include "../includes/minishell.h"

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

static void	process_token(t_token *current, int *has_command, int *error)
{
	if (ft_is_operator(current->type))
	{
		if (ft_check_operator(current) == -1)
			*error = 1;
		*has_command = 0;
	}
	else if (ft_is_redirect(current->type))
	{
		if (ft_check_redirect(current) == -1)
			*error = 1;
	}
	else if (current->type == TOKEN_WORD)
		*has_command = 1;
}

int	ft_lexer_valid(t_token *tokens)
{
	t_token	*current;
	int		has_command;
	int		error;

	if (!tokens)
		return (1);
	current = tokens;
	if (ft_is_operator(current->type))
		return (-1);
	has_command = 0;
	error = 0;
	while (current && !error)
	{
		process_token(current, &has_command, &error);
		current = current->next;
	}
	if (error)
		return (-1);
	return (1);
}
