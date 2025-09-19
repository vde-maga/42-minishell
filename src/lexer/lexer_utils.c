#include "../includes/minishell.h"

void	ft_lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && lexer->input[lexer->pos] && 
		(lexer->input[lexer->pos] == ' ' || lexer->input[lexer->pos] == '\t'))
	{
		lexer->pos++;
		if (lexer->pos >= lexer->len)
			lexer->current_char = '\0';
		else
			lexer->current_char = lexer->input[lexer->pos];
	}
}

void ft_lexer_advance(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos >= lexer->len)
		lexer->current_char = '\0';
	else
		lexer->current_char = lexer->input[lexer->pos];
}
