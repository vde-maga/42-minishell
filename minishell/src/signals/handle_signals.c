/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:41 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 20:19:28 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals_block_execution(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGPIPE, &sa, NULL);
}

/*
 * FUNCTION: ft_signals_handle_signals
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Sets up signal handlers for interactive shell mode with proper
 *   handling of SIGINT and SIGQUIT signals
 *
 * PARAMETERS
 *   void
 *
 * RETURN VALUE
 *   void
 *
 * NOTES
 *   - SIGINT handled by ft_signals_signal_main for clean interrupt
 *   - SIGQUIT ignored in interactive mode (no core dumps)
 *   - Uses SA_RESTART to restart interrupted system calls
 *   - Clears signal mask to prevent blocking other signals
 *   - Critical for proper interactive shell behavior
 *   - Called when returning to interactive prompt
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_signals_handle_signals(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &ft_signals_signal_main;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_signals_heredoc_collect(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = &ft_signals_heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

/*
 * FUNCTION: ft_signals_set_fork1_signal
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Sets default signal handlers for child processes to ensure
 *   proper signal behavior after fork() but before exec()
 *
 * PARAMETERS
 *   void
 *
 * RETURN VALUE
 *   void
 *
 * NOTES
 *   - Resets SIGINT, SIGQUIT, and SIGPIPE to default behavior
 *   - Uses SIG_DFL to restore system default handlers
 *   - No SA_RESTART flag (different from parent process)
 *   - Essential for child processes to handle signals correctly
 *   - Called in child process after fork()
 *   - Prevents inherited signal handlers from interfering
 *   - Signal safety: ensures consistent signal state
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_signals_set_fork1_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
}
