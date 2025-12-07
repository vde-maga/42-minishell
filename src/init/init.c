#include "minishell.h"

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
		ft_set_env_var(&env_list, "SHLVL", "1");
		return ;
	}
	new_shlvl = ft_atoi(shlvl_node->value);
	if (new_shlvl >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(new_shlvl, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		new_shlvl = 1;
	}
	else if (new_shlvl < 1)
		new_shlvl = 1;
	ft_init_shlvl_update(env_list, new_shlvl);
}

static void	ft_init_vars_defaults(t_minishell *ms_data)
{
	ms_data->env = NULL;
	ms_data->input_line = NULL;
	ms_data->input = NULL;
	ms_data->tokens = NULL;
	ms_data->parser = NULL;
	ms_data->lexer = NULL;
	ms_data->hdc_delim = NULL;
	ms_data->shell_pid = 0;
	ms_data->exit_status = 0;
	ms_data->print_flag = 0;
	ms_data->hdc_fds[0] = -1;
	ms_data->hdc_fds[1] = -1;
	ms_data->saved_stdin = -1;
	ms_data->saved_stdout = -1;
	ms_data->in_heredoc = 0;
	ms_data->shell_pid = get_shell_pid_from_proc();
	ft_exit_code(0);
}

void	ft_init_vars(t_minishell *ms_data, char **envp, int ac, char **av)
{
	(void) ac;
	(void) av;
	ms_data->env_list = ft_get_env_list(envp);
	ft_init_shlvl(ms_data->env_list);
	ft_init_vars_defaults(ms_data);
}
