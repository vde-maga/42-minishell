#include "minishell.h"

void	ft_handle_execve_error(char *cmd_name, char **env_array,
				t_minishell *ms_data)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	ft_free_str_arrays(env_array);
	ft_free_shell_child(ms_data);
	if (errno == EACCES || errno == EISDIR)
		_exit(126);
	_exit(127);
}

void	ft_handle_path_not_found(char *cmd_name, char **env_array,
				t_minishell *ms_data)
{
	if (errno == EISDIR)
	{
		ft_printf("%s: Is a directory\n", cmd_name);
		ft_free_str_arrays(env_array);
		ft_free_shell_child(ms_data);
		_exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_free_str_arrays(env_array);
	ft_free_shell_child(ms_data);
	_exit(127);
}