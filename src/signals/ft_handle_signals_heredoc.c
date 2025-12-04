#include "minishell.h"

t_minishell	*shell_struct(t_minishell *shell, int flag)
{
	static t_minishell	*ptr;

	if (flag)
		return (ptr);
	ptr = shell;
	return (ptr);
}

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
