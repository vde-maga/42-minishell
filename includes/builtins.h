#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_builtin_pwd(void);
int	ft_builtin_cd(t_minishell *data, char *path);
int	ft_builtin_echo(char **args);
int	ft_builtin_unset(t_minishell *msdata, char *key);
int	ft_builtin_env(t_minishell *msdata);
int	ft_builtin_export(t_minishell *msdata, char *arg);
int	ft_builtin_exit(t_minishell *msdata, char **args);

#endif