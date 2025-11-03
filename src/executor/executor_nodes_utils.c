#include "minishell.h"

void	ft_exec_child_process(t_minishell *ms_data, t_cmd_node *cmd)
{
	char	**env_array;

	ft_signal_set_fork1_signal();
	if (ft_exec_apply_redirects(cmd) < 0)
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

int	ft_exec_check_invalid_commands(char **args)
{
	if (args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: '': command not found\n", 2);
		return (127);
	}
	if (ft_strcmp(args[0], "..") == 0)
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		return (127);
	}
	return (0);
}

int	ft_exec_wait_and_get_status(pid_t pid, t_minishell *ms_data)
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

int	ft_exec_handle_empty_command(t_cmd_node *cmd)
{
	if (cmd && cmd->redirs)
		return (ft_exec_apply_redirects(cmd));
	return (0);
}

int	ft_exec_fork_and_exec_external(t_minishell *ms_data, t_cmd_node *cmd)
{
	pid_t	pid;

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
	return (ft_exec_wait_and_get_status(pid, ms_data));
}
