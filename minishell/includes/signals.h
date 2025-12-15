/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:15 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 20:19:57 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void			ft_signals_handle_signals(void);
void			ft_signals_set_fork1_signal(void);
void			ft_signals_block_execution(void);
void			ft_signals_heredoc_collect(void);
void			ft_signals_heredoc_handler(int signal);

void			ft_signals_heredoc_signal(void);

// Exit_code
sig_atomic_t	ft_exit_code(int value);
t_minishell		*shell_struct(t_minishell *shell, int flag);

void			ft_signals_heredoc_handler(int signal);
void			ft_signals_signal_main(int signal);

#endif
