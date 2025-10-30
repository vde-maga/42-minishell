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
	shlvl++;
	if (shlvl >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(shlvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		shlvl = 1;
	}
	else if (shlvl < 1)
		shlvl = 1;
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
	ms_data->env = NULL;
	ms_data->input_line = NULL;
	ms_data->input = NULL;
	ms_data->tokens = NULL;
	ms_data->parser = NULL;
	ms_data->print_flag = 0;
	ms_data->shell_pid = get_shell_pid_from_proc();
	ft_exit_code(0);
}

