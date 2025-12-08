/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_nodes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:07 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:08 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_exec_child_process
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Executes an external command in a child process after applying
 *   redirections and resolving the command path
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @cmd: Command node containing arguments and redirections
 *
 * RETURN VALUE
 *   void (function exits with _exit() on success or error)
 *
 * NOTES
 *   - Called from child process after fork()
 *   - Sets default signal handlers for child process
 *   - Applies all redirections before execution
 *   - Resolves command path using PATH environment variable
 *   - Updates "_" environment variable with executed command
 *   - Uses execve() to replace process image
 *   - Never returns - exits on success or error
 *   - Memory cleanup handled before exit
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_exec_child_process(t_minishell *ms_data, t_cmd_node *cmd)
{
	char	**env_array;

	ft_signals_set_fork1_signal();
	if (ft_exec_apply_redirects(cmd) < 0)
	{
		ft_free_shell_child(ms_data);
		_exit(1);
	}
	if (!ft_exec_replace_cmd_with_path(ms_data, cmd))
		ft_handle_path_not_found(cmd->args[0], NULL, ms_data);
	ft_update_env_var(ms_data->env_list, "_", cmd->args[0]);
	env_array = ft_env_list_to_array(ms_data->env_list);
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

/*
 * FUNCTION: ft_exec_wait_and_get_status
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Waits for child process completion and processes exit status
 *   to determine appropriate exit code and signal handling
 *
 * PARAMETERS
 *   @pid: Process ID of the child to wait for
 *   @ms_data: Minishell data structure containing state and flags
 *
 * RETURN VALUE
 *   Exit code of the child process (0 = success, non-zero = error)
 *
 * NOTES
 *   - Uses waitpid() to wait for specific child process
 *   - Restores signal handling after child completion
 *   - Handles both normal exit and signal termination
 *   - Prints appropriate messages for SIGQUIT and SIGINT
 *   - Sets exit code to 128 + signal number for signal termination
 *   - Uses print_flag to prevent duplicate signal messages
 *   - Signal safety: ensures proper cleanup after waiting
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_wait_and_get_status(pid_t pid, t_minishell *ms_data)
{
	int	status;

	waitpid(pid, &status, 0);
	ft_signals_handle_signals();
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

int	ft_exec_handle_empty_command(t_minishell *ms_data, t_cmd_node *cmd)
{
	if (cmd && cmd->redirs)
	{
		if (ft_exec_save_standard_fds(ms_data) < 0)
		{
			ft_close_heredoc_fds(cmd);
			return (ft_exit_code(1));
		}
		if (ft_exec_apply_redirects(cmd) < 0)
		{
			ft_exec_restore_standard_fds(ms_data);
			ft_close_heredoc_fds(cmd);
			return (ft_exit_code(1));
		}
		ft_exec_restore_standard_fds(ms_data);
	}
	ft_close_heredoc_fds(cmd);
	return (ft_exit_code(0));
}

/*
 * FUNCTION: ft_exec_fork_and_exec_external
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Forks a child process and executes an external command,
 *   handling the complete lifecycle of process creation and cleanup
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @cmd: Command node containing arguments and redirections
 *
 * RETURN VALUE
 *   Exit code of the executed command (0 = success, non-zero = error)
 *
 * NOTES
 *   - Blocks signals during critical fork operation
 *   - Handles fork failure with proper cleanup and error reporting
 *   - Parent process closes heredoc file descriptors
 *   - Parent waits for child completion and processes exit status
 *   - Child process never returns (executed by ft_exec_child_process)
 *   - Signal safety: ensures consistent signal state across fork
 *   - Memory management: proper cleanup on all execution paths
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_fork_and_exec_external(t_minishell *ms_data, t_cmd_node *cmd)
{
	pid_t	pid;
	int		status;

	ft_signals_block_execution();
	pid = fork();
	if (pid == -1)
	{
		ft_signals_handle_signals();
		ft_close_heredoc_fds(cmd);
		perror("fork");
		return (ft_exit_code(1));
	}
	if (pid == 0)
		ft_exec_child_process(ms_data, cmd);
	ft_close_heredoc_fds(cmd);
	status = ft_exec_wait_and_get_status(pid, ms_data);
	return (status);
}
