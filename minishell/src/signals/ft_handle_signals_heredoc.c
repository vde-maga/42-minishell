/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:39 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:48:58 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*shell_struct(t_minishell *shell, int flag)
{
	static t_minishell	*ptr;

	if (flag)
		return (ptr);
	ptr = shell;
	return (ptr);
}

/*
 * FUNCTION: ft_signals_heredoc_sigint_handler
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Signal handler for SIGINT during heredoc input collection,
 *   provides clean termination and resource cleanup
 *
 * PARAMETERS
 *   @signal: Signal number (always SIGINT for this handler)
 *
 * RETURN VALUE
 *   void (function exits with _exit())
 *
 * NOTES
 *   - Called when user presses Ctrl+C during heredoc input
 *   - Cleans up heredoc file descriptors and memory
 *   - Uses _exit() instead of exit() for signal safety
 *   - Retrieves shell data via static shell_struct() function
 *   - Exits with code 130 (standard for SIGINT)
 *   - Signal-safe: only uses async-signal-safe operations
 * ─────────────────────────────────────────────────────────────────────────
 */
static void	ft_signals_heredoc_sigint_handler(int signal)
{
	t_minishell	*ms_data;

	(void)signal;
	ms_data = shell_struct(NULL, 1);
	write(2, "\n", 1);
	if (ms_data)
	{
		if (ms_data->hdc_fds[0] >= 0)
			close(ms_data->hdc_fds[0]);
		if (ms_data->hdc_fds[1] >= 0)
			close(ms_data->hdc_fds[1]);
		if (ms_data->hdc_delim)
			free(ms_data->hdc_delim);
		ft_free_shell_child(ms_data);
	}
	_exit(130);
}

/*
 * FUNCTION: ft_signals_heredoc_signal
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Sets up signal handlers specifically for heredoc input mode
 *   with custom SIGINT handling and SIGQUIT ignoring
 *
 * PARAMETERS
 *   void
 *
 * RETURN VALUE
 *   void
 *
 * NOTES
 *   - SIGINT handled by custom heredoc handler for clean interruption
 *   - SIGQUIT ignored during heredoc input (no core dumps)
 *   - No SA_RESTART flag (different from interactive mode)
 *   - Called before entering heredoc input collection
 *   - Ensures proper signal behavior during heredoc processing
 *   - Critical for preventing heredoc input corruption
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_signals_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_signals_heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
