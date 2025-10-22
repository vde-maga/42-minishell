#include "minishell.h"

static void	ft_init_shlvl(t_env *env_list)
{
	t_env	*shlvl_node;
	int		shlvl;
	char	*new_shlvl;

	shlvl_node = ft_get_env_var(env_list, "SHLVL");
	if (!shlvl_node)
	{
		ft_set_env_var(&env_list, "SHLVL", "1");
		return ;
	}
	shlvl = ft_atoi(shlvl_node->value);
	if (shlvl < 0)
		shlvl = 0;
	shlvl++;
	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	ft_update_env_var(env_list, "SHLVL", new_shlvl);
	free(new_shlvl);
}

void ft_init_vars(t_minishell *ms_data, char **envp)
{
	ms_data->env_list = ft_get_env_list(envp);
	ft_init_shlvl(ms_data->env_list);
	ms_data->env = ft_get_path_dirs(ms_data->env_list);
	ms_data->input_line = NULL;
	ms_data->input = NULL;
	ms_data->exit_status = -1;
}

