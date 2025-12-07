#include <minishell.h>
#include "free_helpers.h"

void	ft_free_shell(t_minishell *ms_data, int is_child)
{
	if (!ms_data)
		return ;
	ft_free_shell_data(ms_data);
	ft_close_shell_fds(ms_data);
	ft_cleanup_gnl_buffer(STDIN_FILENO);
	ft_free_env_list(ms_data->env_list);
	if (is_child)
		ft_free_child_resources(ms_data);
}

// Wrapper functions for backward compatibility
void	ft_free_shell_child(t_minishell *ms_data)
{
	ft_free_shell(ms_data, 1);
}
