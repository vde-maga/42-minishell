#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

void	ft_signal_handle_signals(void);

// Exit_code
int	ft_exit_code(int value);

#endif
