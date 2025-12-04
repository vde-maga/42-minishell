#include "minishell.h"

void	ft_exit_failure(t_minishell *ms_data, char *error)
{
	ft_free_shell(ms_data, 0);
	ft_putendl_fd(error, 2);
	exit(1);
}
