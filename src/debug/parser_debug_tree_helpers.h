#ifndef PARSER_DEBUG_TREE_HELPERS_H
# define PARSER_DEBUG_TREE_HELPERS_H

# include "minishell.h"

const char			*get_token_type_name(t_token_type type);
void				print_prefix(char *prefix);
void				print_cmd_details(t_cmd_node *cmd);
void				print_node_type(t_parser_node *node);
void				print_parser_tree(t_parser_node *node, char *prefix,
						int is_left);

#endif