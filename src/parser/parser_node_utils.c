#include "minishell.h"

t_parser_node	*ft_parser_new_node(t_node_type type)
{
	t_parser_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node_type));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}