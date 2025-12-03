#ifndef EXECUTOR_H
# define EXECUTOR_H

void	ft_executor(t_minishell *ms_data, t_parser_node *parser);
int		ft_exec_node(t_minishell *ms_data, t_parser_node *node);
char	**ft_get_path_dirs(t_env *env);
char	*ft_get_cmd_path(char *cmd, t_env *env_list);
int		ft_exec_replace_cmd_with_path(t_minishell *ms_data, t_cmd_node *cmd);
int		ft_exec_is_builtin(char *cmd);
int		ft_exec_run_builtin(t_minishell *ms_data, char **args);
int		ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd);
int		ft_exec_pipe_node(t_minishell *ms_data, t_parser_node *node);
int		ft_process_redir(t_redir *redir);
int		ft_exec_apply_redirects(t_cmd_node *cmd);
int		ft_exec_builtin_with_redirects(t_minishell *ms_data, t_cmd_node *cmd);
void	ft_handle_execve_error(char *cmd_name, char **env_array,
			t_minishell *ms_data);
void	ft_handle_path_not_found(char *cmd_name, char **env_array,
			t_minishell *ms_data);

//	Exec_Nodes_Utils
int		ft_exec_check_invalid_commands(char **args);
int		ft_exec_handle_empty_command(t_cmd_node *cmd);
int		ft_wait_and_get_status(pid_t pid, t_minishell *ms_data);
int		ft_exec_fork_and_exec_external(t_minishell *ms_data, t_cmd_node *cmd);
void	ft_close_heredoc_fds(t_cmd_node *cmd);

//	Error
void	ft_executor_error_eacces(char *cmd_name);
void	ft_executor_error_eoent(char *cmd_name);
void	ft_executor_error_eisdir(char *cmd_name);

#endif
