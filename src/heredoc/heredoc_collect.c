/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:32:04 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 11:50:23 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_eof_warning(char *delim)
{
	write(STDERR_FILENO, "\n", 1);
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

static int	ft_handle_heredoc_line(t_minishell *ms, char *delim,
	int was_quoted, t_token *tok)
{
	char	*line;
	char	*trimmed;

	line = readline("heredoc> ");
	if (!line)
	{
		if (ft_exit_code(-1) == 130)
		{
			free(tok->heredoc_content);
			tok->heredoc_content = NULL;
			return (-1);
		}
		return (ft_heredoc_eof_warning(delim), 1);
	}
	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (ft_strcmp(trimmed, delim) == 0)
		return (free(trimmed), 1);
	tok->heredoc_content = ft_join_heredoc_line(tok->heredoc_content,
			trimmed, was_quoted, ms);
	free(trimmed);
	return (0);
}

static int	ft_collect_single_heredoc(t_minishell *ms, t_token *heredoc_tok)
{
	char	*clean_delim;
	int		was_quoted;
	int		result;

	if (!heredoc_tok->next || heredoc_tok->next->type != TOKEN_WORD)
		return (-1);
	was_quoted = heredoc_tok->next->was_quoted;
	clean_delim = ft_remove_quotes(heredoc_tok->next->value);
	if (!clean_delim)
		return (-1);
	heredoc_tok->heredoc_content = ft_strdup("");
	if (!heredoc_tok->heredoc_content)
		return (free(clean_delim), -1);
	while (1)
	{
		result = ft_handle_heredoc_line(ms, clean_delim, was_quoted,
				heredoc_tok);
		if (result != 0)
			break ;
	}
	free(clean_delim);
	if (result == -1)
		return (-1);
	return (0);
}

/*
 * FUNCTION: ft_collect_heredocs
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Collects all heredoc content from tokens before execution
 *
 * PARAMETERS
 *   ms: Minishell data structure containing tokens
 *
 * RETURN VALUE
 *   0 on success, -1 on error
 *
 * NOTES
 *   - Iterates through token list looking for heredoc tokens
 *   - Collects content for each heredoc before command execution
 *   - Handles delimiter matching and content storage
 *   - Processes variable expansion based on quoting
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_collect_heredocs(t_minishell *ms)
{
	t_token	*current;
	int		result;
	int		stdin_backup;

	if (!ms || !ms->tokens)
		return (0);
	stdin_backup = dup(STDIN_FILENO);
	ms->in_heredoc = 1;
	ft_signals_heredoc_collect();
	current = ms->tokens;
	result = 0;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (ft_collect_single_heredoc(ms, current) < 0)
			{
				result = -1;
				break ;
			}
		}
		current = current->next;
	}
	ms->in_heredoc = 0;
	if (result == -1 && ft_exit_code(-1) == 130)
	{
		dup2(stdin_backup, STDIN_FILENO);
	}
	close(stdin_backup);
	ft_signals_handle_signals();
	return (result);
}
