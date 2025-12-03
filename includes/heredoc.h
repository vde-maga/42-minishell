#ifndef HEREDOC_H
# define HEREDOC_H

int		ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted);
int		ft_process_heredocs(t_minishell *ms_data, t_cmd_node *cmd);
char	*ft_get_var_value(t_minishell *ms_data, char *var_name, int len);
int		ft_get_var_name_len(char *str);
int		ft_is_var_char(char c, char next_c);
char	*ft_append_var(t_minishell *ms_data, char *result, char *line, int *i);
char	*ft_append_char(char *result, char c);
char	*ft_heredoc_readline(int fd);

#endif