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
    t_token_type    type;
    char            *filename;
    struct s_redir  *next;
}   t_redir;

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
}   t_ast_node;
#endif