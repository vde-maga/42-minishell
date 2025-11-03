#include "minishell.h"
#include "exit_utils.h"

int	ft_handle_mixed_quotes_exit(char *arg)
{
	char	*processed;
	int		is_valid_numeric;
	int		exit_code;

	processed = ft_remove_quotes_from_arg(arg);
	if (!processed)
		return (-1);
	if (processed[0] == '\0')
		return (free(processed), -1);
	is_valid_numeric = ft_check_if_numeric(processed);
	exit_code = -1;
	if (is_valid_numeric)
		exit_code = ft_atoi(processed) % 256;
	free(processed);
	return (exit_code);
}

int	ft_handle_quoted_exit(char *arg)
{
	char	*unquoted;
	int		len;
	int		is_valid_numeric;
	int		exit_code;

	if (!ft_is_properly_quoted(arg))
		return (ft_handle_mixed_quotes_exit(arg));
	len = ft_strlen(arg);
	unquoted = malloc(len - 1);
	if (!unquoted)
		return (-1);
	ft_strlcpy(unquoted, arg + 1, len - 1);
	is_valid_numeric = ft_check_if_numeric(unquoted);
	exit_code = -1;
	if (is_valid_numeric)
		exit_code = ft_atoi(unquoted) % 256;
	return (free(unquoted), exit_code);
}

int	ft_process_single_arg(t_minishell *msdata, char *arg)
{
	long long	exit_code;

	exit_code = ft_atoll(arg);
	ft_exit_free_and_exit(msdata, exit_code % 256);
	return (0);
}

int	ft_handle_no_args(t_minishell *msdata)
{
	int	exit_code;

	exit_code = ft_exit_code(-1);
	ft_exit_free_and_exit(msdata, exit_code);
	return (0);
}
