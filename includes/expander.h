#ifndef EXPANDER_H
# define EXPANDER_H

t_token	*ft_expander(t_token *tokens, t_env *env);
int	ft_expand_variables(t_token *tokens, t_env *env);
int	ft_expand_quotes(t_token *tokens);
char	*ft_remove_quotes(char *str);

#endif
