#ifndef STRUCTS_H
# define STRUCTS_H

# include <limits.h>
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_token			t_token;
typedef struct s_lexer			t_lexer;
typedef struct s_parser_node	t_parser_node;

typedef struct s_env
{
	char						*var;
	char						*value;
	int							has_value;
	struct s_env				*next;
}								t_env;

typedef struct s_minishell
{
	char						**env;
	t_token						*tokens;
	t_lexer						*lexer;
	t_env						*env_list;
	t_parser_node				*parser;
	char						*input_line;
	char						*input;
	int							hdc_fds[2];
	char						*hdc_delim;
	int							saved_stdin;
	int							saved_stdout;
	char						cwd[PATH_MAX];
	int							exit_status;
	int							print_flag;
	int							shell_pid;
}								t_minishell;

#endif
