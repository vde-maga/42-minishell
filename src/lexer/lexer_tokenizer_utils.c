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
	if (new_token->value && new_token->value[0])
	{
		int len = ft_strlen(new_token->value);
		int i;
		// int in_single_quote = 0;
		// int in_double_quote = 0;
		int has_quotes = 0;
		
		// Check if the token contains any quotes
		for (i = 0; i < len; i++)
		{
			if (new_token->value[i] == '\'' || new_token->value[i] == '"')
			{
				has_quotes = 1;
				break;
			}
		}
		
		if (has_quotes)
		{
			new_token->was_quoted = 1;
			
			// Check if it's wrapped in the same type of quotes
			char first = new_token->value[0];
			if ((first == '\'' || first == '"')
				&& len > 1 && new_token->value[len - 1] == first)
			{
				// Verify that the quotes are properly matched
				int quote_count = 0;
				for (i = 0; i < len; i++)
				{
					if (new_token->value[i] == first)
						quote_count++;
				}
				
				// If we have an even number of the same quote type,
				// and it starts and ends with that quote, mark it
				if (quote_count == 2)
					new_token->quote = first;
			}
		}
	}
}