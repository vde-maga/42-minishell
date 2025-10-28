#ifndef EXECUTOR_H
# define EXECUTOR_H

void    ft_executor(t_minishell *ms_data, t_parser_node *parser);
int     ft_exec_node(t_minishell *ms_data, t_parser_node *node);
char	**ft_get_path_dirs(t_env *env);
char	*ft_get_cmd_path(char *cmd, t_env *env_list);
int     ft_exec_replace_cmd_with_path(t_minishell *ms_data, t_cmd_node *cmd);
int     ft_exec_is_builtin(char *cmd);
int 	ft_exec_run_builtin(t_minishell *ms_data, char **args);
int     ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd);
int     ft_exec_pipe_node(t_minishell *ms_data, t_parser_node *node);
int     ft_process_redir(t_redir *redir);
int     ft_apply_redirects(t_cmd_node *cmd);
int     ft_exec_builtin_with_redirects(t_minishell *ms_data, t_cmd_node *cmd);
void	ft_handle_execve_error(char *cmd_name, char **env_array,
			t_minishell *ms_data);
void	ft_handle_path_not_found(char *cmd_name, char **env_array,
			t_minishell *ms_data);

#endif
