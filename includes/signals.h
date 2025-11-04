#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_signal_handle_signals(void);
void	ft_signal_set_fork1_signal(void);
void	ft_signal_set_main_signals(void);

void	ft_signals_heredoc_signal(void);

// Exit_code
int		ft_exit_code(int value);

#endif
