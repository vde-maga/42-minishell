#include "minishell.h"

int	ft_heredoc_from_content(char *content)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		return (-1);
	if (content)
		write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
	return (pipefd[0]);
}

int	ft_heredoc_parent(pid_t pid, int *pipefd)
{
	int	status;
	int	exit_code;
	int	read_fd;

	close(pipefd[1]);
	pipefd[1] = -1;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_signals_handle_signals();
	ft_signals_heredoc_signal();
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 130)
		{
			ft_exit_code(130);
			close(pipefd[0]);
			pipefd[0] = -1;
			return (-1);
		}
	}
	read_fd = pipefd[0];
	pipefd[0] = -1;
	return (read_fd);
}
