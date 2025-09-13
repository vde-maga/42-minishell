#ifndef STRUCTS_H
# define STRUCTS_H

#include <limits.h>
#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

typedef struct s_minishell
{
	char	**env;
	char	*input_line;
	char	*input;
	char	cwd[PATH_MAX];
	int	exit_status;
} t_minishell;

#endif
