#include "minishell.h"

static void	ft_init_shlvl_create(t_env *env_list)
{
	ft_set_env_var(&env_list, "SHLVL", "1");
}

static int	ft_init_shlvl_calculate(int current_shlvl)
{
	int	new_shlvl;

	new_shlvl = current_shlvl;
	if (new_shlvl >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(new_shlvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		new_shlvl = 1;
	}
	else if (new_shlvl < 1)
		new_shlvl = 1;
	return (new_shlvl);
}

static void	ft_init_shlvl_update(t_env *env_list, int new_shlvl)
{
	char	*new_shlvl_str;

	new_shlvl_str = ft_itoa(new_shlvl);
	if (!new_shlvl_str)
		return ;
	ft_update_env_var(env_list, "SHLVL", new_shlvl_str);
	free(new_shlvl_str);
}

static void	ft_init_shlvl(t_env *env_list)
{
	t_env	*shlvl_node;
	int		new_shlvl;

	shlvl_node = ft_get_env_var(env_list, "SHLVL");
	if (!shlvl_node)
	{
		ft_init_shlvl_create(env_list);
		return ;
	}
	new_shlvl = ft_init_shlvl_calculate(ft_atoi(shlvl_node->value));
	ft_init_shlvl_update(env_list, new_shlvl);
}

void	ft_init_vars(t_minishell *ms_data, char **envp, int ac, char **av)
{
	(void) ac;
	(void) av;
	ms_data->env_list = ft_get_env_list(envp);
	ft_init_shlvl(ms_data->env_list);
	ms_data->env = NULL;
	ms_data->input_line = NULL;
	ms_data->input = NULL;
	ms_data->tokens = NULL;
	ms_data->parser = NULL;
	ms_data->print_flag = 0;
	ms_data->hdc_fds[0] = -1;
	ms_data->hdc_fds[1] = -1;
	ms_data->hdc_delim = NULL;
	ms_data->shell_pid = get_shell_pid_from_proc();
	ft_exit_code(0);
}
