/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:19 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:20 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_process_redir
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Processes a single redirection by dispatching to the appropriate
 *   handler based on redirection type
 *
 * PARAMETERS
 *   @redir: Redirection structure containing type and target information
 *
 * RETURN VALUE
 *   0 on success, negative value on error (specific to redirection type)
 *
 * NOTES
 *   - Handles input (<), output (>), force output (>),
 *     append (>>), and heredoc (<<)
 *   - Both TOKEN_REDIRECT_OUT and TOKEN_FORCE_REDIRECT_OUT use same handler
 *   - Error codes propagate up through the execution chain
 *   - File descriptor management handled by individual handlers
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_process_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIRECT_IN)
		return (ft_handle_redirect_in(redir));
	else if (redir->type == TOKEN_REDIRECT_OUT)
		return (ft_handle_redirect_out(redir));
	else if (redir->type == TOKEN_FORCE_REDIRECT_OUT)
		return (ft_handle_redirect_out(redir));
	else if (redir->type == TOKEN_APPEND)
		return (ft_handle_append(redir));
	else if (redir->type == TOKEN_HEREDOC)
		return (ft_handle_heredoc(redir));
	return (0);
}
