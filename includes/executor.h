#ifndef EXECUTOR_H
# define EXECUTOR_H

void    ft_executor(t_minishell *ms_data, t_parser_node *parser);

char	**ft_get_path_dirs(t_env *env);
char	*ft_get_cmd_path(char *cmd, char **envp);

#endif
