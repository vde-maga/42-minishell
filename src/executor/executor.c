#include "minishell.h"

int	ft_exec_replace_cmd_with_path(t_minishell *ms_data, t_cmd_node *cmd)
{
	char	*full_path;

	full_path = ft_get_cmd_path(cmd->args[0], ms_data->env_list);
	if (full_path)
	{
		free(cmd->args[0]);
		cmd->args[0] = full_path;
		return (1);
	}
	free(full_path);
	return (0);
}

/*
 * FUNCTION: ft_exec_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Executes a parsed AST node by dispatching to appropriate handlers
 *   based on node type (command, subshell, logical operators, pipe)
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @node: AST node to execute
 *
 * RETURN VALUE
 *   Exit code of the executed command (0 = success, non-zero = error)
 *
 * NOTES
 *   - Handles logical AND (&&) and OR (||) operators with short-circuiting
 *   - Recursive function that processes the entire AST tree
 *   - Memory management is handled by child functions
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_node(t_minishell *ms_data, t_parser_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (ft_exec_cmd_node(ms_data, node->cmd_data));
	else if (node->type == NODE_SUBSHELL)
		return (ft_exec_subshell(ms_data, node->left));
	else if (node->type == NODE_AND)
	{
		ft_exec_node(ms_data, node->left);
		if (ft_exit_code(-1) == 0)
			ft_exec_node(ms_data, node->right);
		return (ft_exit_code(-1));
	}
	else if (node->type == NODE_OR)
	{
		ft_exec_node(ms_data, node->left);
		if (ft_exit_code(-1) != 0)
			ft_exec_node(ms_data, node->right);
		return (ft_exit_code(-1));
	}
	else if (node->type == NODE_PIPE)
		return (ft_exec_pipe_node(ms_data, node));
	return (0);
}

/*
 * FUNCTION: ft_executor
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Main entry point for command execution from the parsed AST
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @parser: Root AST node containing the complete command structure
 *
 * RETURN VALUE
 *   void (exit code is stored globally via ft_exit_code)
 *
 * NOTES
 *   - Acts as the primary interface between parser and executor
 *   - Validates parser input before execution
 *   - Global exit code is used to communicate execution status
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_executor(t_minishell *ms_data, t_parser_node *parser)
{
	if (!parser)
	{
		ft_printf("executor: parser (null)");
		return ;
	}
	ft_exec_node(ms_data, parser);
}

/*
 * FUNCTION: ft_exec_subshell
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Executes commands in a subshell by forking a child process
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @node: AST node representing the subshell command(s)
 *
 * RETURN VALUE
 *   Exit code of the subshell execution (0 = success, non-zero = error)
 *
 * NOTES
 *   - Creates isolated process environment for subshell execution
 *   - Child process exits with the command's exit code
 *   - Parent waits for child completion and propagates exit status
 *   - Signal safety: handles SIGINT and SIGQUIT appropriately
 *   - Memory cleanup occurs in both parent and child processes
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_subshell(t_minishell *ms_data, t_parser_node *node)
{
	pid_t	pid;
	int		status;

	if (!node)
		return (1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		ft_exec_node(ms_data, node);
		ft_free_shell(ms_data, 1);
		exit(ft_exit_code(-1));
	}
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		ft_exit_code(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		ft_exit_code(128 + WTERMSIG(status));
	else
		ft_exit_code(1);
	return (ft_exit_code(-1));
}
