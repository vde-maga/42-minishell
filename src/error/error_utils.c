#include "minishell.h"

// Unified error message printing function
void	ft_print_error(char *cmd_name, char *error_msg, char *additional)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd_name)
		ft_putstr_fd(cmd_name, 2);
	if (cmd_name && error_msg)
		ft_putstr_fd(": ", 2);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	if (additional)
	{
		if (error_msg)
			ft_putstr_fd(additional, 2);
		else
			ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd("\n", 2);
}

// Specialized error functions using the unified function
void	ft_executor_error_eacces(char *cmd_name)
{
	ft_print_error(cmd_name, "Permission denied", NULL);
}

void	ft_executor_error_eisdir(char *cmd_name)
{
	ft_print_error(cmd_name, "Is a directory", NULL);
}

void	ft_executor_error_eoent(char *cmd_name)
{
	ft_print_error(cmd_name, "No such file or directory", NULL);
}

void	ft_print_syntax_error(char *token_value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token_value && token_value[0])
		ft_putstr_fd(token_value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}
