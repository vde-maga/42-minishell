/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:21 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:17 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_exec_apply_redirects
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Applies all redirections associated with a command by iterating
 *   through the redirection list and processing each one
 *
 * PARAMETERS
 *   @cmd: Command node containing the list of redirections to apply
 *
 * RETURN VALUE
 *   0 on success, -1 on error (redirection failure)
 *
 * NOTES
 *   - Processes redirections in order (important for multiple redirects)
 *   - Handles input (<), output (>), append (>>), and heredoc (<<) redirects
 *   - Early termination on first redirection failure
 *   - File descriptor management handled by ft_process_redir
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: ft_exec_save_standard_fds
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Saves the current standard input and output file descriptors
 *   so they can be restored later (typically after builtin execution)
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure to store the saved file descriptors
 *
 * RETURN VALUE
 *   0 on success, -1 on error (dup() failure)
 *
 * NOTES
 *   - Uses dup() to create copies of STDIN_FILENO and STDOUT_FILENO
 *   - Stores saved descriptors in ms_data structure
 *   - Proper cleanup on error (closes any successfully duplicated fds)
 *   - Critical for builtin commands with redirections
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: ft_exec_restore_standard_fds
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Restores previously saved standard input and output file descriptors
 *   to their original state
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing the saved file descriptors
 *
 * RETURN VALUE
 *   void
 *
 * NOTES
 *   - Uses dup2() to restore original file descriptors
 *   - Closes saved descriptors after restoration
 *   - Resets saved descriptor values to -1 (invalid)
 *   - Safe to call even if no descriptors were saved
 *   - Essential for builtin commands with redirections
 * ─────────────────────────────────────────────────────────────────────────
 */
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

static int	ft_cleanup_return(t_minishell *ms, t_cmd_node *cmd,
	int rest, int ret)
{
	if (rest)
		ft_exec_restore_standard_fds(ms);
	ft_signals_handle_signals();
	ft_close_heredoc_fds(cmd);
	return (ft_exit_code(ret), ret);
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
			return (ft_cleanup_return(ms_data, cmd, 0, 1));
		if (ft_exec_apply_redirects(cmd) < 0)
			return (ft_cleanup_return(ms_data, cmd, 1, 1));
	}
	ret = ft_exec_run_builtin(ms_data, cmd->args);
	if (ft_strcmp(cmd->args[0], "exit") == 0 && ret == 1)
		return (ft_cleanup_return(ms_data, cmd, has_redirs, 1));
	return (ft_cleanup_return(ms_data, cmd, has_redirs, ret));
}
