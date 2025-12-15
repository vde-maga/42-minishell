/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:18:50 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 20:19:33 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_signals_signal_main
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Main signal handler for interactive shell mode, handles SIGINT (Ctrl+C)
 *   by providing clean prompt redisplay and setting appropriate exit code
 *
 * PARAMETERS
 *   @signal: Signal number received (typically SIGINT)
 *
 * RETURN VALUE
 *   void
 *
 * NOTES
 *   - Only handles SIGINT in interactive mode
 *   - Prints newline and redisplays prompt cleanly
 *   - Clears current input line with rl_replace_line()
 *   - Sets exit code to 130 (standard for SIGINT)
 *   - Uses readline functions for proper prompt management
 *   - Signal-safe: only uses async-signal-safe operations
 * ─────────────────────────────────────────────────────────────────────────
 */

void	ft_signals_signal_main(int signal)
{
	t_minishell	*ms_data;

	if (signal == SIGINT)
	{
		ms_data = shell_struct(NULL, 1);
		write(2, "\n", 1);
		ft_exit_code(130);
		if (ms_data && ms_data->in_heredoc)
			return ;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signals_heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		ft_exit_code(130);
		rl_replace_line("", 0);
		rl_done = 1;
		close(STDIN_FILENO);
	}
}
