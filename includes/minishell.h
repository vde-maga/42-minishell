#ifndef MINISHELL_H
# define MINISHELL_H

# include "42_libft/libft.h"
# include "42_ft_printf/ft_printf.h"
# include "42_get_next_line/get_next_line.h"
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "wrappers.h"
# include "heredoc.h"
# include "expander.h"

# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void    get_str_readline(t_minishell *ms_data, int type);

// ---------------------- Init -------------------------------------------------
void	ft_init_vars(t_minishell *ms_data);
t_env	*ft_get_env_list(char **envp);
void	ft_free_env_list(t_env *head);

// ---------------------- Error ------------------------------------------------
void	ft_exit_failure(t_minishell *ms_data, char *error);
void	ft_free_shell(t_minishell *ms_data);
int	ft_input_validation(t_minishell *ms_data);
#endif
