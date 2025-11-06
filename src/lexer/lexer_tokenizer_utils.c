#include "../includes/minishell.h"

void	ft_lex_add_single_operator(t_lexer *lexer, char current)
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

void	ft_lex_add_double_operator(t_lexer *lexer, char current, char next)
{
	if (current == '|' && next == '|')
		ft_add_token(lexer, TOKEN_OR, NULL);
	else if (current == '<' && next == '<')
		ft_add_token(lexer, TOKEN_HEREDOC, NULL);
	else if (current == '>' && next == '>')
		ft_add_token(lexer, TOKEN_APPEND, NULL);
	else if (current == '&' && next == '&')
		ft_add_token(lexer, TOKEN_AND_IF, NULL);
	ft_lexer_advance(lexer);
	ft_lexer_advance(lexer);
}

static void	count_quotes(const char *value, int *single, int *dbl)
{
	int	i;

	i = 0;
	*single = 0;
	*dbl = 0;
	while (value && value[i])
	{
		if (value[i] == '\'')
			(*single)++;
		else if (value[i] == '"')
			(*dbl)++;
		i++;
	}
}

void	ft_tok_check_quoted(t_token *new_token)
{
	int	len;
	int	single_quote_count;
	int	double_quote_count;

	new_token->quote = 0;
	new_token->was_quoted = 0;
	if (!new_token->value || !new_token->value[0])
		return ;
	len = ft_strlen(new_token->value);
	count_quotes(new_token->value, &single_quote_count, &double_quote_count);
	if (single_quote_count > 0 || double_quote_count > 0)
	{
		new_token->was_quoted = 1;
		if (new_token->value[0] == '\'' && new_token->value[len - 1] == '\''
			&& single_quote_count == 2)
			new_token->quote = '\'';
		else if (new_token->value[0] == '"' && new_token->value[len - 1] == '"'
			&& double_quote_count == 2)
			new_token->quote = '"';
	}
}
