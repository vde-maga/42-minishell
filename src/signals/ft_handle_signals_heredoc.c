#include "signals.h"

/*
** @brief The handler for SIGINT (Ctrl+C) during a heredoc.
**
** @details This function is designed to be async-signal-safe. When Ctrl+C is
**          pressed during heredoc input (which runs in a child process), this
**          handler writes a newline and then immediately exits the process with
**          status 130.
**          The call to exit() is safe and ensures the OS cleans up all resources
**          (memory, file descriptors), avoiding unsafe functions like free() or
**          close() inside a signal handler.
**
** @param sig The signal number (expected to be SIGINT).
*/
static void	ft_heredoc_sigint_handler(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	exit(130);
}

/*
** @brief Sets the signal handlers for a child process handling a heredoc.
**
** @details It uses sigaction for robust signal handling:
**          - SIGINT (Ctrl+C): Is caught by `heredoc_sigint_handler`, which
**            terminates the process. `sa_flags` is 0 to ensure that blocking
**            system calls like read() are interrupted by the signal.
**          - SIGQUIT (Ctrl+\): Is set to be ignored (SIG_IGN), as is standard
**            shell behavior during input.
*/
void	ft_signals_heredoc_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
