#include "minishell.h"

int	ft_lex_read_word(t_lexer *lexer);

static int	ft_is_fd_redir(t_lexer *lexer)
{
	t_token	*last;
	int		fd;

	if (!lexer->tokens)
		return (-1);
	last = lexer->tokens;
	while (last->next)
		last = last->next;
	if (last->type != TOKEN_WORD || !last->value)
		return (-1);
	if (ft_strlen(last->value) != 1 || !ft_isdigit(last->value[0]))
		return (-1);
	if (last->was_quoted)
		return (-1);
	fd = last->value[0] - '0';
	return (fd);
}

static void	ft_remove_last_token(t_lexer *lexer)
{
	t_token	*curr;
	t_token	*prev;

	if (!lexer->tokens)
		return ;
	if (!lexer->tokens->next)
	{
		ft_token_free(lexer->tokens);
		lexer->tokens = NULL;
		return ;
	}
	curr = lexer->tokens;
	prev = NULL;
	while (curr->next)
	{
		prev = curr;
		curr = curr->next;
	}
	ft_token_free(curr);
	if (prev)
		prev->next = NULL;
}

static void	ft_set_last_token_fd(t_lexer *lexer, int fd)
{
	t_token	*last;

	if (!lexer->tokens)
		return ;
	last = lexer->tokens;
	while (last->next)
		last = last->next;
	last->redir_fd = fd;
}

static int	ft_lex_add_operator(t_lexer *lexer)
{
	char	c;
	char	n;
	int		fd;

	c = lexer->input[lexer->pos];
	n = lexer->input[lexer->pos + 1];
	fd = -1;
	if (c == '>' || c == '<')
		fd = ft_is_fd_redir(lexer);
	if (fd >= 0)
		ft_remove_last_token(lexer);
	if ((c == '|' && n == '|') || (c == '<' && n == '<') || (c == '>'
			&& n == '>') || (c == '&' && n == '&') || (c == '>' && n == '|'))
		ft_lex_add_double_operator(lexer, c, n);
	else if (c == '|' || c == '<' || c == '>' || c == '&'
		|| c == '(' || c == ')')
		ft_lex_add_single_operator(lexer, c);
	else
		return (0);
	if (fd >= 0)
		ft_set_last_token_fd(lexer, fd);
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
