#include "minishell.h"

int	ft_check_operator(t_token *token)
{
	if (!token->next)
		return (-1);
	if (ft_is_operator(token->next->type))
		return (-1);
	if (token->next->type == TOKEN_EOF)
		return (-1);
	return (1);
}

void	ft_lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && lexer->input[lexer->pos]
		&& (lexer->input[lexer->pos] == ' '
			|| lexer->input[lexer->pos] == '\t'))
	{
		lexer->pos++;
		if (lexer->pos >= lexer->len)
			lexer->current_char = '\0';
		else
			lexer->current_char = lexer->input[lexer->pos];
	}
}

void	ft_lexer_advance(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos >= lexer->len)
		lexer->current_char = '\0';
	else
		lexer->current_char = lexer->input[lexer->pos];
}
