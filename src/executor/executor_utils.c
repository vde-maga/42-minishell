/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:24 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:25 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_exec_is_builtin
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Determines if a command is a builtin function by checking against
 *   the list of supported builtin commands
 *
 * PARAMETERS
 *   @cmd: Command name to check
 *
 * RETURN VALUE
 *   1 if command is a builtin, 0 otherwise
 *
 * NOTES
 *   - Supports: cd, echo, pwd, export, unset, env, exit
 *   - Case-sensitive comparison
 *   - Returns 0 for NULL input for safety
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	ft_exec_handle_dot_builtin(char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd("minishell: usage: . filename [arguments]\n", 2);
		return (2);
	}
	return (0);
}

int	ft_exec_run_primary_builtins(t_minishell *ms_data, char **args)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_builtin_pwd());
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_builtin_cd(ms_data, args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_builtin_echo(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (ft_builtin_unset(ms_data, args));
	return (-1);
}

int	ft_exec_run_secondary_builtins(t_minishell *ms_data, char **args)
{
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_builtin_env(ms_data, args));
	if (ft_strcmp(args[0], "export") == 0)
		return (ft_builtin_export(ms_data, args));
	if (ft_strcmp(args[0], "exit") == 0)
		return (ft_builtin_exit(ms_data, &args[1]));
	if (ft_strcmp(args[0], ".") == 0)
		return (ft_exec_handle_dot_builtin(args));
	return (-1);
}

/*
 * FUNCTION: ft_exec_run_builtin
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Executes builtin commands by dispatching to appropriate handler
 *   functions based on command type
 *
 * PARAMETERS
 *   @ms_data: Minishell data structure containing environment and state
 *   @args: Command arguments array (args[0] is the command name)
 *
 * RETURN VALUE
 *   Exit code of builtin command (0 = success, non-zero = error)
 *   Returns -1 if command is not a builtin
 *
 * NOTES
 *   - First checks primary builtins (cd, echo, pwd, unset)
 *   - Then checks secondary builtins (env, export, exit, .)
 *   - Two-tier system for optimization and organization
 *   - NULL-safe input handling
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exec_run_builtin(t_minishell *ms_data, char **args)
{
	int	exit_code;

	if (args == NULL || args[0] == NULL)
		return (0);
	exit_code = ft_exec_run_primary_builtins(ms_data, args);
	if (exit_code != -1)
		return (exit_code);
	exit_code = ft_exec_run_secondary_builtins(ms_data, args);
	if (exit_code != -1)
		return (exit_code);
	return (-1);
}
