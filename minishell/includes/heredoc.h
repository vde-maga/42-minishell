/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:03 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:44:02 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

/* heredoc.c */
int		ft_heredoc_error(char *clean_delim);
int		ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted);
int		ft_process_heredocs(t_minishell *ms_data, t_cmd_node *cmd);

/* heredoc_parent.c */
int		ft_heredoc_from_content(char *content);
int		ft_heredoc_parent(pid_t pid, int *pipefd);

/* heredoc_child.c */
void	ft_heredoc_child(t_minishell *ms_data, char *clean_delim,
			int was_quoted, int *pipefd);

/* heredoc_expand.c */
char	*ft_get_var_value(t_minishell *ms_data, char *var_name, int len);
int		ft_get_var_name_len(char *str);
int		ft_is_var_char(char c, char next_c);
char	*ft_process_heredoc_line(t_minishell *ms_data, char *line,
			int was_quoted);

/* heredoc_utils.c */
char	*ft_append_var(t_minishell *ms_data, char *result, char *line, int *i);
char	*ft_append_char(char *result, char c);
char	*ft_heredoc_readline(int fd);

/* heredoc_collect.c */
int		ft_collect_heredocs(t_minishell *ms);

#endif
