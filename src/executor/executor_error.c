#include "minishell.h"

void	ft_handle_execve_error(char *cmd_name, char **env_array,
				t_minishell *ms_data)
{
	if (errno == EACCES)
		ft_executor_error_eacces(cmd_name);
	else if (errno == EISDIR)
		ft_executor_error_eisdir(cmd_name);
	else if (errno == ENOENT)
		ft_executor_error_eoent(cmd_name);
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
	t_env	*path_var;

	if (errno == EISDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_free_str_arrays(env_array);
		ft_free_shell_child(ms_data);
		_exit(126);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	path_var = ft_get_env_var(ms_data->env_list, "PATH");
	if (ft_strchr(cmd_name, '/') || !path_var || !path_var->value)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	ft_free_str_arrays(env_array);
	ft_free_shell_child(ms_data);
	_exit(127);
}
