#ifndef EXIT_HANDLERS_H
# define EXIT_HANDLERS_H

# include "minishell.h"

int	ft_handle_mixed_quotes_exit(char *arg);
int	ft_handle_quoted_exit(char *arg);
int	ft_process_single_arg(t_minishell *msdata, char *arg);
int	ft_handle_no_args(t_minishell *msdata);
int	ft_handle_two_args(t_minishell *msdata, char **args);

#endif