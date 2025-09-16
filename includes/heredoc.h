#ifndef HEREDOCS_H
# define HEREDOCS_H


int ft_heredoc(t_minishell *ms_data, char *delimiter);
char	*ft_strip_quotes_local(char *s);
void ft_test_heredoc(t_minishell *ms);

#endif