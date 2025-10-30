#include "signals.h"

static void	ft_heredoc_sigint_handler(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	exit(130);
}

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
