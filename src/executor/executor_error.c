#include "minishell.h"

void	ft_handle_execve_error(char *cmd_name, char **env_array,
				t_minishell *ms_data)
{
	if (errno == EACCES)
		ft_printf("%s: Permission denied\n", cmd_name);
	else if (errno == EISDIR)
		ft_printf("%s: Is a directory\n", cmd_name);
	else if (errno == ENOENT)
		ft_printf("%s: No such file or directory\n", cmd_name);
	else
		ft_printf("%s: %s\n", cmd_name, strerror(errno));
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
	ft_printf("%s: command not found\n", cmd_name);
	ft_free_str_arrays(env_array);
	ft_free_shell_child(ms_data);
	_exit(127);
}