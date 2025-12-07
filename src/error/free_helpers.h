#ifndef FREE_HELPERS_H
# define FREE_HELPERS_H

# include "minishell.h"

void	ft_free_str_arrays(char **str);
void	ft_free_shell_data(t_minishell *ms_data);
void	ft_close_shell_fds(t_minishell *ms_data);
void	ft_free_child_resources(t_minishell *ms_data);

#endif