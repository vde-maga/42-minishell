#include "../includes/minishell.h"

t_token	*ft_get_token_before(t_token *tokens, t_token *target);

static int	ft_check_parentheses(t_token *tokens)
{
	t_token	*current;
	int		paren_count;

	current = tokens;
	paren_count = 0;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			paren_count++;
		else if (current->type == TOKEN_RPAREN)
		{
			paren_count--;
			if (paren_count < 0)
				return (-1);
		}
		current = current->next;
	}
	if (paren_count != 0)
		return (-1);
	return (1);
}

static int	ft_check_parentheses_content(t_token *tokens)
{
	t_token	*current;
	int		in_paren;

	current = tokens;
	in_paren = 0;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
		{
			in_paren++;
			if (current->next && current->next->type == TOKEN_RPAREN)
				return (-1);
		}
		else if (current->type == TOKEN_RPAREN)
			in_paren--;
		else if (in_paren && current->type == TOKEN_EOF)
			return (-1);
		current = current->next;
	}
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

static void	process_token(t_token *tokens, t_token *current,
	int *has_command, int *error)
{
	t_token	*prev;

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
	else if (current->type == TOKEN_LPAREN)
		*has_command = 0;
	else if (current->type == TOKEN_RPAREN)
	{
		prev = ft_get_token_before(tokens, current);
		if (!prev || (prev->type != TOKEN_WORD && prev->type != TOKEN_RPAREN))
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
	if (ft_check_parentheses(tokens) == -1)
		return (-1);
	if (ft_check_parentheses_content(tokens) == -1)
		return (-1);
	current = tokens;
	if (ft_is_operator(current->type) || current->type == TOKEN_RPAREN)
		return (-1);
	has_command = 0;
	error = 0;
	while (current && !error)
	{
		process_token(tokens, current, &has_command, &error);
		current = current->next;
	}
	if (error)
		return (-1);
	return (1);
}
