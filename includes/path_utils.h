#ifndef PATH_UTILS_H
# define PATH_UTILS_H

# include "minishell.h"

char	*ft_get_variable_value(t_env *env, char *var_name);
char	*ft_path_tilde_expand(t_env *env, const char *path);
char	*ft_path_tilde_shorten(t_env *env, const char *path);
int		get_shell_pid_from_proc(void);

#endif
