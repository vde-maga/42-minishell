#include "minishell.h"

sig_atomic_t	ft_exit_code(int value)
{
	static volatile sig_atomic_t	code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}
