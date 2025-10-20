#include "../includes/minishell.h"

static int	ft_lex_add_operator(t_lexer *lexer)
{
	char	c;
	char	n;

	c = lexer->input[lexer->pos];
	n = lexer->input[lexer->pos + 1];
	
	if ((c == '|' && n == '|') || (c == '<' && n == '<') || (c == '>' && n == '>')
            || (c == '&' && n == '&'))
		ft_lex_add_double_operator(lexer, c, n);
    else if (c == '|' || c == '<' || c == '>' || c == '&')
		ft_lex_add_single_operator(lexer, c);
	else
		return (0);
	return (1);
}

static int	ft_lex_read_word(t_lexer *lexer)
{
    int start_pos;

    start_pos = lexer->pos;
    while (lexer->pos < lexer->len && lexer->input[lexer->pos] && ft_isprint_byte((int)lexer->input[lexer->pos]))
    {
        char c = lexer->input[lexer->pos];
        if (c == '\'' || c == '"')
        {
            char q = c;
            ft_lexer_advance(lexer);
            while (lexer->pos < lexer->len && lexer->input[lexer->pos] && lexer->input[lexer->pos] != q)
                ft_lexer_advance(lexer);
            if (lexer->pos >= lexer->len || lexer->input[lexer->pos] == '\0')
                return (2);
            ft_lexer_advance(lexer);
            continue;
        }
        if (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>' || c == '&')
            break;
        ft_lexer_advance(lexer);
    }

    if (lexer->pos == start_pos)
        return (0);
    {
        int length = lexer->pos - start_pos;
        char *word = malloc(length + 1);
        if (!word)
            return (-1);
        ft_strlcpy(word, &lexer->input[start_pos], length + 1);
        ft_add_token(lexer, TOKEN_WORD, word);
    }
    return (1);
}

int	ft_lexer_tokenize(t_lexer *lexer)
{
	int	r;

    while (lexer->pos < lexer->len && lexer->input[lexer->pos] != '\0')
    {
        ft_lexer_skip_spaces(lexer);
        if (lexer->pos >= lexer->len || lexer->input[lexer->pos] == '\0')
            break ;
        if (ft_lex_add_operator(lexer))
            continue ;
        if (ft_isprint_byte((int)lexer->input[lexer->pos]))
        {
            r = ft_lex_read_word(lexer);
            if (r == -1)
                return (0);
            if (r == 2)
                return (2);
            if (r == 1)
                continue ;
        }
        ft_lexer_advance(lexer);
    }
    return (1);
}

