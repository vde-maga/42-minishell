#ifndef EXPANDER_H
# define EXPANDER_H

t_token	*ft_expander(t_minishell *msdata, t_env *env);
int	ft_expand_variables(t_minishell *msdata, t_env *env);
int	ft_expand_quotes(t_token *tokens);
char	*ft_remove_quotes(char *str);
int	ft_exp_replace_content(t_env *env, t_token *current, char *var_name);
int	ft_exp_special_param(t_minishell *msdata, t_token *current, char *var_name);
int	is_valid_env_var_name(char *str);
int	is_valid_special_param(char *str);
int get_shell_pid_from_proc(void);

#endif
