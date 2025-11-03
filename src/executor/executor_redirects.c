#include "minishell.h"

int	ft_apply_redirects(t_cmd_node *cmd)
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

int	ft_exec_builtin_with_redirects(t_minishell *ms_data, t_cmd_node *cmd)
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
		return (ft_exit_code(1), 1);
	}
	if (ft_apply_redirects(cmd) < 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (ft_exit_code(1), 1);
	}
	ret = ft_exec_run_builtin(ms_data, cmd->args);
	if (ft_strcmp(cmd->args[0], "exit") == 0 && ret == 1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		ft_exit_code(1);
		return (1);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	ft_exit_code(ret);
	return (ret);
}
