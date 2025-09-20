#include "minishell.h"

void ft_init_vars(t_minishell *ms_data, char **envp)
{
	ms_data->env_list = ft_get_env_list(envp);
	ms_data->env = ft_get_path_dirs(ms_data->env_list);
	ms_data->input_line = NULL;
	ms_data->input = NULL;
	ms_data->exit_status = -1;
}
