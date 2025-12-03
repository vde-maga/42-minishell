#include "minishell.h"

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
