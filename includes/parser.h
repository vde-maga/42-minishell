#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_node_type
{
    NODE_CMD,       // Command
    NODE_PIPE,      // pipe |
    NODE_AND,       // AND lógico &&
    NODE_OR         // OR lógico ||
}   t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	int				fd;
	int				was_quoted;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd_node
{
    char            **args;
    t_redir         *redirs;
}   t_cmd_node;

typedef struct s_parser_node
{
    t_node_type     type;
    struct s_parser_node *left;
    struct s_parser_node *right;
    t_cmd_node      *cmd_data;
    int             in_fd;
    int             out_fd;
}   t_parser_node;


// TODO: Function name are tooo long, it helps to build the tree, but its not readable at all

// ft_parser.c
t_parser_node	*ft_parser(t_token *tokens);
t_parser_node	*ft_parser_build_node_tree(t_token *tokens);

// parser_node_utils.c
t_parser_node	*ft_parser_new_node(t_node_type type);
int			ft_parser_count_args(t_token *tokens);
void			ft_parser_add_redirect(t_cmd_node *cmd_data, t_token *redirect_tok);

// parser_utils.c
t_token			*ft_parser_find_last_operator(t_token *tokens,
                    t_token_type type1, t_token_type type2);
t_parser_node	*ft_parse_command(t_token *tokens);

// Free helpers: free parser AST and related structures
void		ft_parser_free(t_parser_node *node);

#endif