#include "minishell.h"

void	ft_free_shell(t_minishell *ms_data)
{
	if (!ms_data)
		return;
	clear_history();
	if (ms_data->env)
		free(ms_data->env);
	if (ms_data->input_line)
		free(ms_data->input_line);
	if (ms_data->input)
		free(ms_data->input);
}

void	ft_exit_failure(t_minishell *ms_data, char *error)
{
	//TODO: create free minishell data function
	ft_free_shell(ms_data);
	ft_putendl_fd(error, 2);
	exit(1);
}
