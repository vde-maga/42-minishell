/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:07 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:44:08 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "error.h"
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
int			ft_count_array_elements(char **array, char delimiter);
int			ft_count_words(char *str);
// String append modes for ft_string_append
typedef enum e_append_mode
{
	APPEND_CHAR,
	APPEND_STRING,
	APPEND_READLINE
}	t_append_mode;

void		ft_free_linked_list(void *list, void (*free_func)(void *));
void		ft_free_token_node(void *token);
void		ft_free_redir_node(void *redir);
char		*ft_string_append(char *original, char *to_append, int append_mode);

// ---------------------- User Input -------------------------------------------
void		get_str_readline(t_minishell *ms_data, int type);
void		ft_usr_print_prompt(t_minishell *ms_data, int type, char *prompt);
void		ft_usr_print_prompt_color(t_minishell *ms_data, int type,
				char *prompt);
void		ft_prompt_print_default(t_minishell *ms_data, char *prompt);
void		ft_prompt_print_incomplete(char *prompt);
void		ft_cleanup_gnl_buffer(int fd);

// ---------------------- Init -------------------------------------------------
void		ft_init_vars(t_minishell *ms_data, char **envp, int ac, char **av);

// ---------------------- Error ------------------------------------------------
void		ft_exit_failure(t_minishell *ms_data, char *error);
void		ft_free_shell(t_minishell *ms_data, int is_child);
void		ft_free_shell_child(t_minishell *ms_data);
void		ft_free_str_arrays(char **str);

int			ft_isprint_byte(int c);
#endif
