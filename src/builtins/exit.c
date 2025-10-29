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

static int	ft_handle_quoted_exit(char *arg)
{
	char	*unquoted;
	int		len;
	int		j;
	int		is_valid_numeric;
	int		exit_code;

	len = ft_strlen(arg);
	if (len <= 2 || arg[0] != '"' || arg[len - 1] != '"')
		return (-1);
	unquoted = malloc(len - 1);
	if (!unquoted)
		return (-1);
	ft_strlcpy(unquoted, arg + 1, len - 1);
	is_valid_numeric = 1;
	j = 0;
	while (unquoted[j])
	{
		if (!ft_isdigit(unquoted[j]))
			is_valid_numeric = 0;
		j++;
	}
	exit_code = -1;
	if (is_valid_numeric)
		exit_code = ft_atoi(unquoted) % 256;
	return (free(unquoted), exit_code);
}

static int	ft_process_single_arg(t_minishell *msdata, char *arg)
{
	int	exit_code;

	exit_code = ft_handle_quoted_exit(arg);
	if (exit_code != -1)
		return (ft_exit_free_and_exit(msdata, exit_code), 0);
	if (ft_is_numeric(arg))
	{
		exit_code = ft_atoi(arg) % 256;
		return (ft_exit_free_and_exit(msdata, exit_code), 0);
	}
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (ft_exit_free_and_exit(msdata, 2), 0);
}

int	ft_builtin_exit(t_minishell *msdata, char **args)
{
	int	exit_code;
	int	arg_count;

	if (msdata && msdata->shell_pid == get_shell_pid_from_proc()
		&& isatty(STDERR_FILENO))
		ft_putstr_fd("exit\n", 2);
	arg_count = 0;
	while (args && args[arg_count])
		arg_count++;
	if (arg_count == 0)
	{
		exit_code = ft_exit_code(-1);
		return (ft_exit_free_and_exit(msdata, exit_code), 0);
	}
	if (arg_count > 2)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	if (arg_count == 1)
		return (ft_process_single_arg(msdata, args[0]));
	if (!ft_is_numeric(args[0]))
		return (ft_process_single_arg(msdata, args[0]));
	exit_code = ft_atoi(args[0]) % 256;
	return (ft_exit_free_and_exit(msdata, exit_code), 0);
}

