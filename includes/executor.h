#ifndef EXECUTOR_H
# define EXECUTOR_H

void    ft_executor(t_minishell *ms_data, t_parser_node *parser);
int     ft_exec_node(t_minishell *ms_data, t_parser_node *node);

char	**ft_get_path_dirs(t_env *env);
char	*ft_get_cmd_path(char *cmd, char **envp);
int     ft_exec_replace_cmd_with_path(t_minishell *ms_data, t_cmd_node *cmd);
int     ft_exec_is_builtin(char *cmd);
int 	ft_exec_run_builtin(t_minishell *ms_data, char **args);
int     ft_exec_cmd_node(t_minishell *ms_data, t_cmd_node *cmd);
int     ft_exec_pipe_node(t_minishell *ms_data, t_parser_node *node);

int     ft_process_redir(t_redir *redir);
int     ft_apply_redirects(t_cmd_node *cmd);
int     ft_exec_builtin_with_redirects(t_minishell *ms_data, t_cmd_node *cmd);

#endif
