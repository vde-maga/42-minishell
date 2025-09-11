#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_minishell
{
	char	**env;
	char	*input_line;
	char	*input;
	char	*cwd;
	int	exit_status;
} t_minishell;

#endif
