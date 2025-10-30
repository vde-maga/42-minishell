#include "../includes/minishell.h"

void    ft_lex_add_single_operator(t_lexer *lexer, char current)
{
    if (current == '|')
		ft_add_token(lexer, TOKEN_PIPE, NULL);
	else if (current == '<')
		ft_add_token(lexer, TOKEN_REDIRECT_IN, NULL);
	else if (current == '>')
		ft_add_token(lexer, TOKEN_REDIRECT_OUT, NULL);
	else if (current == '&')
		ft_add_token(lexer, TOKEN_AND, NULL);
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
	if (!new_token->value || !new_token->value[0])
		return;
		
	int len = ft_strlen(new_token->value);
	int i;
	int has_quotes = 0;
	int single_quote_count = 0;
	int double_quote_count = 0;
	
	// Count quotes and check if token contains any quotes
	for (i = 0; i < len; i++)
	{
		if (new_token->value[i] == '\'')
		{
			has_quotes = 1;
			single_quote_count++;
		}
		else if (new_token->value[i] == '"')
		{
			has_quotes = 1;
			double_quote_count++;
		}
	}
	
	if (has_quotes)
	{
		new_token->was_quoted = 1;
		
		// Check if it's wrapped in quotes (single or double)
		char first = new_token->value[0];
		char last = new_token->value[len - 1];
		
		// Single quote wrapping
		if (first == '\'' && last == '\'' && single_quote_count == 2)
			new_token->quote = '\'';
		// Double quote wrapping
		else if (first == '"' && last == '"' && double_quote_count == 2)
			new_token->quote = '"';
		// For mixed quotes, don't set quote type but keep was_quoted
		// This allows proper handling in expansion
	}
}