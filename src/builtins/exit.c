#include "minishell.h"
#include "exit_utils.h"
#include "exit_handlers.h"

int	ft_is_numeric(char *str)
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

void	ft_exit_free_and_exit(t_minishell *msdata, int exit_code)
{
	if (msdata && msdata->tokens)
		ft_tokens_free(msdata->tokens);
	if (msdata && msdata->parser)
		ft_parser_free(msdata->parser);
	if (msdata)
		ft_free_shell(msdata);
	exit(exit_code);
}

static int	ft_is_llong(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (str[i] == '\0');
}

int	ft_builtin_exit(t_minishell *msdata, char **args)
{
	int	arg_count;

	if (msdata && msdata->shell_pid == get_shell_pid_from_proc()
		&& isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	arg_count = ft_count_args(args);
	if (arg_count == 0)
		return (ft_handle_no_args(msdata));
	if (!ft_is_numeric(args[0]) || !ft_is_llong(args[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit_free_and_exit(msdata, 2);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit_code(2);
		return (2);
	}
	return (ft_process_single_arg(msdata, args[0]));
}
