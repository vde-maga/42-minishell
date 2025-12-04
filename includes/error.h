#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

// Unified error printing function
void	ft_print_error(char *cmd_name, char *error_msg, char *additional);

// Specialized error functions
void	ft_executor_error_eacces(char *cmd_name);
void	ft_executor_error_eisdir(char *cmd_name);
void	ft_executor_error_eoent(char *cmd_name);
void	ft_print_syntax_error(char *token_value);

#endif