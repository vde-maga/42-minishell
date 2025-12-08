/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:37 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:29:38 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_heredoc_token(t_minishell *ms, t_token *current)
{
	char	*delim;
	int		quoted;
	int		fd;

	if (current->next && current->next->type == TOKEN_WORD)
	{
		delim = current->next->value;
		quoted = current->next->was_quoted;
		fd = ft_heredoc(ms, delim, quoted);
		if (fd >= 0)
		{
			ft_printf("[heredoc] delimiter='%s' -> fd=%d\n", delim, fd);
			close(fd);
		}
		else
			ft_printf("[heredoc] delimiter='%s' -> interrupted/error\n",
				delim);
	}
	else
		ft_printf("[heredoc] missing delimiter token\n");
}

void	ft_test_heredoc(t_minishell *ms)
{
	t_token	*current;

	current = ms->tokens;
	if (!current)
		return ;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
			process_heredoc_token(ms, current);
		current = current->next;
	}
}
