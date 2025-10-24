#ifndef HEREDOCS_H
# define HEREDOCS_H

int	ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted);
int	ft_process_heredocs(t_minishell *ms_data, t_cmd_node *cmd);

#endif