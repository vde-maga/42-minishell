#include "minishell.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_exit_free_and_exit(t_minishell *msdata, int exit_code)
{
	if (msdata && msdata->tokens)
		ft_tokens_free(msdata->tokens);
	if (msdata && msdata->parser)
		ft_parser_free(msdata->parser);
	if (msdata)
		ft_free_shell(msdata);
	exit(exit_code);
}

int	ft_builtin_exit(t_minishell *msdata, char **args)
{
	int	exit_code;

	if (msdata && msdata->shell_pid == get_shell_pid_from_proc() 
		&& isatty(STDERR_FILENO))
		ft_putstr_fd("exit\n", 2);
	if (!args || !args[0] || !args[1])
	{
		exit_code = ft_exit_code(-1);
		ft_exit_free_and_exit(msdata, exit_code);
		return (0);
	}
	if (!ft_is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (ft_exit_free_and_exit(msdata, 2), 0);
	}
	if (args[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	exit_code = ft_atoi(args[1]) % 256;
	return (ft_exit_free_and_exit(msdata, exit_code), 0);
}
