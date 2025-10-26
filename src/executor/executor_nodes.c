#include "minishell.h"

static int	ft_apply_redirects(t_cmd_node *cmd)
{
	t_redir	*redir;
	int		fd;

	if (!cmd)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN)
		{
			fd = open(redir->filename, O_RDONLY);
			if (fd < 0)
				return (perror(redir->filename), -1);
			if (dup2(fd, STDIN_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
			close(fd);
		}
		else if (redir->type == TOKEN_REDIRECT_OUT)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (perror(redir->filename), -1);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
			close(fd);
		}
		else if (redir->type == TOKEN_APPEND)
		{
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				return (perror(redir->filename), -1);
			if (dup2(fd, STDOUT_FILENO) < 0)
				return (close(fd), perror("dup2"), -1);
			close(fd);
		}
		else if (redir->type == TOKEN_HEREDOC && redir->fd >= 0)
		{
			if (dup2(redir->fd, STDIN_FILENO) < 0)
				return (close(redir->fd), perror("dup2"), -1);
			close(redir->fd);
		}
		redir = redir->next;
	}
	return (0);
}

static int	ft_exec_builtin_with_redirects(t_minishell *ms_data, t_cmd_node *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
	{
		if (saved_stdin >= 0)
			close(saved_stdin);
		if (saved_stdout >= 0)
			close(saved_stdout);
		return (ms_data->exit_status = 1, 1);
	}
	if (ft_apply_redirects(cmd) < 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (ms_data->exit_status = 1, 1);
	}
	ret = ft_exec_run_builtin(ms_data, cmd->args);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}

int	ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd)
{
	pid_t				pid;
	int					status;
	struct sigaction	sa;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_process_heredocs(ms_data, cmd) < 0)
		return (ms_data->exit_status = 1, 1);
	if (ft_exec_is_builtin(cmd->args[0]))
		return (ft_exec_builtin_with_redirects(ms_data, cmd));
	ft_set_signals_executing();
	pid = fork();
	if (pid == -1)
	{
		ft_printf("fork failed: %s\n", strerror(errno));
		ms_data->exit_status = 1;
		return (1);
	}
	if (pid == 0)
	{
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		if (ft_apply_redirects(cmd) < 0)
		{
			ft_free_shell_child(ms_data);
			_exit(1);
		}
		if (ft_exec_replace_cmd_with_path(ms_data, cmd))
			execve(cmd->args[0], cmd->args, ms_data->env);
		ft_printf("execve failed: %s\n", strerror(errno));
		ft_free_shell_child(ms_data);
		_exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ms_data->exit_status = 128 + WTERMSIG(status);
	ft_handle_signals();
	return (ms_data->exit_status);
}
