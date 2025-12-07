#include "../includes/minishell.h"

static void	handle_quotes(t_lexer *lexer, int *in_single, int *in_double)
{
	char	c;

	c = lexer->input[lexer->pos];
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
	ft_lexer_advance(lexer);
}

static void	process_word_chars(t_lexer *lexer, int *in_s, int *in_d)
{
	char	c;

	while (lexer->pos < lexer->len && lexer->input[lexer->pos]
		&& ft_isprint_byte((int)lexer->input[lexer->pos]))
	{
		c = lexer->input[lexer->pos];
		if (c == '\'' || c == '"')
		{
			handle_quotes(lexer, in_s, in_d);
			continue ;
		}
		if (!*in_s && !*in_d && (c == ' ' || c == '\t'
				|| c == '|' || c == '<' || c == '>' || c == '&'
				|| c == '(' || c == ')'))
			break ;
		ft_lexer_advance(lexer);
	}
}

int	ft_lex_read_word(t_lexer *lexer)
{
	int		start_pos;
	int		in_single_quote;
	int		in_double_quote;
	char	*word;

	in_single_quote = 0;
	in_double_quote = 0;
	start_pos = lexer->pos;
	process_word_chars(lexer, &in_single_quote, &in_double_quote);
	if (in_single_quote || in_double_quote)
		return (2);
	if (lexer->pos == start_pos)
		return (0);
	word = ft_substr(lexer->input, start_pos, lexer->pos - start_pos);
	if (!word)
		return (-1);
	ft_add_token(lexer, TOKEN_WORD, word);
	return (1);
}
