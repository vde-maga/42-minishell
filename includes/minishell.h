#ifndef MINISHELL_H
# define MINISHELL_H

# include "42_libft/libft.h"
# include "42_ft_printf/ft_printf.h"
# include "42_get_next_line/get_next_line.h"
# include "structs.h"
# include "lexer.h"
# include "wrappers.h"

# include <stdio.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/wait.h>

char	*get_str_readline(int type);

// ---------------------- Init -------------------------------------------------
void	ft_init_vars(t_minishell *ms_data);

// ---------------------- Error ------------------------------------------------
void	ft_exit_failure(t_minishell *ms_data, char *error);
#endif
