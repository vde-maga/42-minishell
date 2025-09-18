#ifndef STRUCTS_H
# define STRUCTS_H

# include <limits.h>
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_token t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	char			**env;
	t_token			*tokens;
	t_env			*env_list;
	char			*input_line;
	char			*input;
	int				hdc_fds[2];
	char			cwd[PATH_MAX];
	int				exit_status;
}					t_minishell;

#endif
