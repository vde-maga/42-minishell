#include "minishell.h"

void ft_init_vars(t_minishell *ms_data)
{
	ms_data->env = NULL;
	ms_data->env_list = NULL;
	ms_data->input_line = NULL;
	ms_data->input = NULL;
	ms_data->exit_status = -1;
}
