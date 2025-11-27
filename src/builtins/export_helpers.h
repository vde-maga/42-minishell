#ifndef EXPORT_HELPERS_H
# define EXPORT_HELPERS_H

# include "minishell.h"

int		ft_is_valid_identifier(char *str);
void	ft_env_bubble_sort(t_env **env_array, int count);
void	ft_print_env_var(t_env *env_var);
int		ft_print_env_list(t_minishell *msdata);
int	ft_calculate_allocate_space(char *value);
char	*ft_remove_spaces(char *value);

#endif