#include "minishell.h"

/*
 * FUNCTION: ft_exec_cmd_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Executes a command node by processing heredocs, validating commands,
 *   and dispatching to appropriate execution path (builtin or external)
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @cmd: Command node containing arguments and redirections
 *
 * RETURN VALUE
 *   Exit code of the executed command (0 = success, non-zero = error)
 *
 * NOTES
 *   - Handles heredoc processing before command execution
 *   - Validates command arguments for invalid inputs
 *   - Distinguishes between builtin and external commands
 *   - Ensures proper cleanup of heredoc file descriptors
 *   - Error handling propagates through global exit code
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd)
{
	int	error_code;

	ms_data->print_flag = 0;
	if (ft_process_heredocs(ms_data, cmd) < 0)
	{
		ft_close_heredoc_fds(cmd);
		return (ft_exit_code(-1));
	}
	if (!cmd || !cmd->args || !cmd->args[0])
		return (ft_exec_handle_empty_command(ms_data, cmd));
	error_code = ft_exec_check_invalid_commands(cmd->args);
	if (error_code != 0)
	{
		ft_close_heredoc_fds(cmd);
		return (ft_exit_code(error_code));
	}
	if (ft_exec_is_builtin(cmd->args[0]))
		return (ft_exec_builtin_with_redirects(ms_data, cmd));
	if (ms_data->in_subshell)
		ft_exec_child_process(ms_data, cmd);
	return (ft_exec_fork_and_exec_external(ms_data, cmd));
}
