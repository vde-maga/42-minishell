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
	sa.sa_handler = &ft_signals_signal_main;
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
