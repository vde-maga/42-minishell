#include "minishell.h"
#include "parser_debug_tree_helpers.h"

void	ft_parser_tree_test(t_parser_node *root)
{
	ft_printf("---------- Parser Debugger ------\n");
	print_parser_tree(root, "", 0);
	ft_printf("------- End Parser Debugger -----\n");
}
