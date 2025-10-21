#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_builtin_pwd(void);
int	ft_builtin_cd(t_minishell *data, char *path);
int	ft_builtin_echo(char **args);

#endif