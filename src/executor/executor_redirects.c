#include "minishell.h"

int	ft_exec_apply_redirects(t_cmd_node *cmd)
{
	t_redir	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (ft_process_redir(redir) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	ft_exec_save_standard_fds(t_minishell *ms_data)
{
	ms_data->saved_stdin = dup(STDIN_FILENO);
	ms_data->saved_stdout = dup(STDOUT_FILENO);
	if (ms_data->saved_stdin < 0 || ms_data->saved_stdout < 0)
	{
		perror("dup");
		if (ms_data->saved_stdin >= 0)
			close(ms_data->saved_stdin);
		if (ms_data->saved_stdout >= 0)
			close(ms_data->saved_stdout);
		ms_data->saved_stdin = -1;
		ms_data->saved_stdout = -1;
		return (-1);
	}
	return (0);
}

void	ft_exec_restore_standard_fds(t_minishell *ms_data)
{
	if (ms_data->saved_stdin >= 0)
	{
		dup2(ms_data->saved_stdin, STDIN_FILENO);
		close(ms_data->saved_stdin);
		ms_data->saved_stdin = -1;
	}
	if (ms_data->saved_stdout >= 0)
	{
		dup2(ms_data->saved_stdout, STDOUT_FILENO);
		close(ms_data->saved_stdout);
		ms_data->saved_stdout = -1;
	}
}

int	ft_exec_builtin_with_redirects(t_minishell *ms_data, t_cmd_node *cmd)
{
	int	ret;
	int	has_redirs;

	has_redirs = (cmd && cmd->redirs);
	ft_signals_block_execution();
	if (has_redirs)
	{
		if (ft_exec_save_standard_fds(ms_data) < 0)
		{
			ft_signals_handle_signals();
			ft_close_heredoc_fds(cmd);
			return (ft_exit_code(1), 1);
		}
		if (ft_exec_apply_redirects(cmd) < 0)
		{
			ft_exec_restore_standard_fds(ms_data);
			ft_signals_handle_signals();
			ft_close_heredoc_fds(cmd);
			return (ft_exit_code(1), 1);
		}
	}
	ret = ft_exec_run_builtin(ms_data, cmd->args);
	if (ft_strcmp(cmd->args[0], "exit") == 0 && ret == 1)
	{
		if (has_redirs)
			ft_exec_restore_standard_fds(ms_data);
		ft_signals_handle_signals();
		ft_close_heredoc_fds(cmd);
		return (ft_exit_code(1), 1);
	}
	if (has_redirs)
		ft_exec_restore_standard_fds(ms_data);
	ft_signals_handle_signals();
	ft_close_heredoc_fds(cmd);
	ft_exit_code(ret);
	return (ret);
}
