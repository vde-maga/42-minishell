#ifndef PARSER_H
# define PARSER_H

# include "42_libft/libft.h"
# include "lexer.h"
# include <stdlib.h>

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}							t_node_type;

typedef struct s_redir
{
	t_token_type			type;
	char					*filename;
	int						fd;
	int						was_quoted;
	int						target_fd;
	struct s_redir			*next;
}							t_redir;

typedef struct s_cmd_node
{
	char					**args;
	t_redir					*redirs;
}							t_cmd_node;

typedef struct s_parser_node
{
	t_node_type				type;
	struct s_parser_node	*left;
	struct s_parser_node	*right;
	t_cmd_node				*cmd_data;
	int						in_fd;
	int						out_fd;
}							t_parser_node;

/*
** ft_parser_tree.c
*/
t_parser_node				*ft_parser(t_token *tokens);
t_parser_node				*ft_parser_build_node_tree(t_token *tokens);
t_parser_node				*ft_parser_split_and_build(t_token *tokens,
								t_token *op);
t_token						*ft_get_token_before(t_token *tokens,
								t_token *target);
t_token						*ft_parser_find_last_operator(t_token *tokens,
								t_token_type t1, t_token_type t2);

/*
** ft_parser_cmd.c
*/
t_parser_node				*ft_parse_command(t_token *tokens);
int							ft_populate_cmd_data(t_cmd_node *cmd,
								t_token *toks);
int							ft_handle_word_token(t_cmd_node *cmd, int *i,
								char *value);
int							ft_parser_count_args(t_token *tokens);
t_parser_node				*ft_parser_new_node(t_node_type type);

/*
** ft_parser_redir.c
*/
void						ft_parser_add_redirect(t_cmd_node *cmd,
								t_token *tok);
t_redir						*create_redir_node(t_token *redir_tok);
void						append_redir_to_list(t_cmd_node *cmd_data,
								t_redir *new_redir);

/*
** ft_parser_free.c
*/
void						ft_parser_free(t_parser_node *node);
void						ft_parser_free_cmd_data(t_cmd_node *cmd_data);
void						free_string_array(char **arr);
void						free_redir_list(t_redir *list);

/*
** ft_populate_cmd_data.c
*/

int							init_cmd_args(t_cmd_node *cmd, t_token *toks);
int							process_token_list(t_cmd_node *cmd, t_token *toks);
#endif
