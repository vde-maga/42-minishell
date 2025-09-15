#include "../includes/minishell.h"

void    ft_lex_add_single_operator(t_lexer *lexer, char current)
{
    if (current == '|')
		ft_add_token(lexer, TOKEN_PIPE, NULL);
	else if (current == '<')
		ft_add_token(lexer, TOKEN_REDIRECT_IN, NULL);
	else if (current == '>')
		ft_add_token(lexer, TOKEN_REDIRECT_OUT, NULL);
    ft_lexer_advance(lexer);
}

void    ft_lex_add_double_operator(t_lexer *lexer, char current, char next)
{
    if (current == '|' && next == '|')
		ft_add_token(lexer, TOKEN_OR, NULL);
	else if (current == '<' && next == '<')
		ft_add_token(lexer, TOKEN_HEREDOC, NULL);
	else if (current == '>' && next == '>')
		ft_add_token(lexer, TOKEN_APPEND, NULL);
	else if (current == '&' && next == '&')
		ft_add_token(lexer, TOKEN_AND_IF, NULL);
    ft_lexer_advance(lexer),
    ft_lexer_advance(lexer);
}

void    ft_tok_check_quoted(t_token *new_token)
{
	new_token->quote = 0;
	new_token->was_quoted = 0;
	if (new_token->value && new_token->value[0] &&
		(new_token->value[0] == '\'' || new_token->value[0] == '"'))
	{
		new_token->was_quoted = 1;
		new_token->quote = new_token->value[0];
	}
}