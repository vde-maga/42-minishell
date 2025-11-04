#ifndef MINISHELL_H
# define MINISHELL_H

# include "42_ft_printf/ft_printf.h"
# include "42_get_next_line/get_next_line.h"
# include "42_libft/libft.h"
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "env.h"
# include "path_utils.h"
# include "expander.h"
# include "executor.h"
# include "heredoc.h"
# include "builtins.h"
# include "debug_funcs.h"
# include "signals.h"
# include "wrappers.h"
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
// # include <linux/limits.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

// ---------------------- Utils ------------------------------------------------
long long	ft_atoll(const char *str);

// ---------------------- User Input -------------------------------------------
void		get_str_readline(t_minishell *ms_data, int type);
void		ft_usr_print_prompt(t_minishell *ms_data, int type, char *prompt);
void		ft_usr_print_prompt_color(t_minishell *ms_data, int type,
				char *prompt);
void		ft_prompt_print_default(t_minishell *ms_data, char *prompt);
void		ft_prompt_print_incomplete(char *prompt);

// ---------------------- Init -------------------------------------------------
void		ft_init_vars(t_minishell *ms_data, char **envp, int ac, char **av);

// ---------------------- Error ------------------------------------------------
void		ft_exit_failure(t_minishell *ms_data, char *error);
void		ft_free_shell(t_minishell *ms_data);
void		ft_free_shell_child(t_minishell *ms_data);
void		ft_free_str_arrays(char **str);

int			ft_isprint_byte(int c);
#endif
