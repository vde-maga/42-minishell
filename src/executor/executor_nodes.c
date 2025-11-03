#include "minishell.h"

static void	ft_exec_child_process(t_minishell *ms_data, t_cmd_node *cmd)
{
	char	**env_array;

	ft_signal_set_fork1_signal();
	if (ft_apply_redirects(cmd) < 0)
	{
		ft_free_shell_child(ms_data);
		_exit(1);
	}
	env_array = ft_env_list_to_array(ms_data->env_list);
	if (!ft_exec_replace_cmd_with_path(ms_data, cmd))
		ft_handle_path_not_found(cmd->args[0], env_array, ms_data);
	execve(cmd->args[0], cmd->args, env_array);
	ft_handle_execve_error(cmd->args[0], env_array, ms_data);
}

static int	ft_wait_and_get_status(pid_t pid, t_minishell *ms_data)
{
	int	status;

	waitpid(pid, &status, 0);
	ft_signal_handle_signals();
	if (WIFEXITED(status))
		ft_exit_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (ms_data->print_flag == 0)
		{
			if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			else if (WTERMSIG(status) == SIGINT)
				write(2, "\n", 1);
			ft_exit_code(128 + WTERMSIG(status));
			ms_data->print_flag = 1;
		}
	}
	return (ft_exit_code(-1));
}

int	ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd)
{
	pid_t	pid;

	ms_data->print_flag = 0;
	if (ft_process_heredocs(ms_data, cmd) < 0)
		return (ft_exit_code(1), 1);
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		if (cmd && cmd->redirs)
			return (ft_apply_redirects(cmd));
		return (0);
	}
	if (cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: '': command not found\n", 2);
		return (ft_exit_code(127));
	}
	if (ft_strcmp(cmd->args[0], "..") == 0)
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		return (ft_exit_code(127));
	}
	if (ft_exec_is_builtin(cmd->args[0]))
		return (ft_exec_builtin_with_redirects(ms_data, cmd));
	ft_signal_set_main_signals();
	pid = fork();
	if (pid == -1)
	{
		ft_signal_handle_signals();
		perror("fork");
		return (ft_exit_code(1));
	}
	if (pid == 0)
		ft_exec_child_process(ms_data, cmd);
	return (ft_wait_and_get_status(pid, ms_data));
}
