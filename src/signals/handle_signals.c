#include "signals.h"

void	ft_signal_sig_main(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_exit_code(130);
	}
}

void	ft_signal_sig_pipe(int signal)
{
	if (signal == SIGPIPE)
	{
	}
}

void	ft_signal_set_main_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, ft_signal_sig_pipe);
}

void	ft_signal_handle_signals(void)
{
	signal(SIGINT, ft_signal_sig_main);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_set_fork1_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
