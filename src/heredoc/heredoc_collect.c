#include "minishell.h"

static void	ft_heredoc_eof_warning(char *delim)
{
	ft_putstr_fd("minishell: warning: heredoc delimited by EOF ", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("')\n", 2);
}

static char	*ft_join_heredoc_line(char *content, char *line, int was_quoted,
	t_minishell *ms)
{
	char	*processed;
	char	*new_content;
	char	*with_newline;

	processed = ft_process_heredoc_line(ms, ft_strdup(line), was_quoted);
	if (!processed)
		return (content);
	with_newline = ft_strjoin(processed, "\n");
	free(processed);
	if (!with_newline)
		return (content);
	if (!content)
		return (with_newline);
	new_content = ft_strjoin(content, with_newline);
	return (free(with_newline), free(content), new_content);
}

static int	ft_read_heredoc_content_loop(t_minishell *ms, char *delim,
	int was_quoted, t_token *tok)
{
	char	*line;
	char	*trimmed;

	tok->heredoc_content = NULL;
	while (1)
	{
		if (isatty(fileno(stdin)))
			write(STDERR_FILENO, "heredoc> ", 9);
		line = get_next_line(fileno(stdin));
		if (!line)
			return (ft_heredoc_eof_warning(delim), 0);
		trimmed = ft_strtrim(line, "\n");
		free(line);
		if (ft_strcmp(trimmed, delim) == 0)
			return (free(trimmed), 0);
		tok->heredoc_content = ft_join_heredoc_line(tok->heredoc_content,
				trimmed, was_quoted, ms);
		free(trimmed);
	}
	return (0);
}

static int	ft_collect_single_heredoc(t_minishell *ms, t_token *heredoc_tok)
{
	char	*clean_delim;
	int		was_quoted;

	if (!heredoc_tok->next || heredoc_tok->next->type != TOKEN_WORD)
		return (-1);
	was_quoted = heredoc_tok->next->was_quoted;
	clean_delim = ft_remove_quotes(heredoc_tok->next->value);
	if (!clean_delim)
		return (-1);
	ft_read_heredoc_content_loop(ms, clean_delim, was_quoted, heredoc_tok);
	free(clean_delim);
	return (0);
}

int	ft_collect_heredocs(t_minishell *ms)
{
	t_token	*current;

	if (!ms || !ms->tokens)
		return (0);
	current = ms->tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (ft_collect_single_heredoc(ms, current) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
