#include "minishell.h"

static void	ft_exec_pipe_child_left(t_minishell *ms_data, t_parser_node *node,
	int pipefd[2])
{
	int	status;

	ft_signal_set_fork1_signal();
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[1]);
		ft_free_shell_child(ms_data);
		exit(1);
	}
	close(pipefd[1]);
	status = ft_exec_node(ms_data, node->left);
	ft_free_shell_child(ms_data);
	exit(status);
}

static void	ft_exec_pipe_child_right(t_minishell *ms_data, t_parser_node *node,
	int pipefd[2])
{
	int	status;

	ft_signal_set_fork1_signal();
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		ft_free_shell_child(ms_data);
		exit(1);
	}
	close(pipefd[0]);
	status = ft_exec_node(ms_data, node->right);
	ft_free_shell_child(ms_data);
	exit(status);
}

static void	ft_exec_pipe_wait(pid_t pid1, pid_t pid2, t_minishell *ms_data)
{
	int	status;

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		ft_exit_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (ms_data->print_flag == 0)
		{
			printf("FILHA DE UMA GRANDE PUTAAAAAA\n\n\n\n");
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			else if (WTERMSIG(status) == SIGINT)
				write(2, "\n", 1);
			ft_exit_code(128 + WTERMSIG(status));
			ms_data->print_flag = 1;
		}
	}
	ft_signal_handle_signals();
}

static int	ft_exec_pipe_fork_children(t_minishell *ms_data,
	t_parser_node *node, int pipefd[2])
{
	pid_t	pid1;
	pid_t	pid2;

	ft_signal_set_main_signals();
	pid1 = fork();
	if (pid1 == -1)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
	if (pid1 == 0)
		ft_exec_pipe_child_left(ms_data, node, pipefd);
	pid2 = fork();
	if (pid2 == -1)
	{
		kill(pid1, SIGKILL);
		waitpid(pid1, NULL, 0);
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
	}
	if (pid2 == 0)
		ft_exec_pipe_child_right(ms_data, node, pipefd);
	ft_exec_pipe_wait(pid1, pid2, ms_data);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int	ft_exec_pipe_node(t_minishell *ms_data, t_parser_node *node)
{
	int	pipefd[2];

	if (!node || !node->left || !node->right)
		return (0);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		ft_exit_code(1);
		return (1);
	}
	if (ft_exec_pipe_fork_children(ms_data, node, pipefd) == -1)
	{
		ft_exit_code(1);
		return (1);
	}
	return (ft_exit_code(-1));
}
