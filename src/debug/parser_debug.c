#include "minishell.h"
#include "parser_debug_helpers.h"

void	ft_parser_test(t_token *tokens)
{
	t_parser_node	*root;

	if (!tokens)
	{
		ft_printf("No tokens provided to parser test.\n");
		return ;
	}
	root = ft_parser(tokens);
	ft_printf("--- Parser AST ---\n");
	print_parser_node(root, 0);
	ft_printf("--- End AST ---\n");
	ft_parser_free(root);
}
