#include "minishell.h"

static void	print_indentation(int level)
{
	int i;

	i = 0;
	while (i < level)
	{
		ft_printf("  ");
		i++;
	}
}

static void	print_cmd_node(t_cmd_node *cmd, int level)
{
	int i;

	if (!cmd)
		return;
	print_indentation(level);
	ft_printf("CMD\n");
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			print_indentation(level + 1);
			ft_printf("arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
	}
	if (cmd->redirs)
	{
		t_redir *r;
		r = cmd->redirs;
		while (r)
		{
			print_indentation(level + 1);
			ft_printf("redir: type=%d file=%s\n", r->type, r->filename);
			r = r->next;
		}
	}
}

static void	print_parser_node(t_parser_node *node, int level)
{
	if (!node)
	{
		print_indentation(level);
		ft_printf("(null)\n");
		return;
	}
	print_indentation(level);
	switch (node->type)
	{
		case NODE_CMD:
			ft_printf("NODE_CMD\n");
			print_cmd_node(node->cmd_data, level + 1);
			break;
		case NODE_PIPE:
			ft_printf("NODE_PIPE\n");
			print_parser_node(node->left, level + 1);
			print_parser_node(node->right, level + 1);
			break;
		case NODE_AND:
			ft_printf("NODE_AND\n");
			print_parser_node(node->left, level + 1);
			print_parser_node(node->right, level + 1);
			break;
		case NODE_OR:
			ft_printf("NODE_OR\n");
			print_parser_node(node->left, level + 1);
			print_parser_node(node->right, level + 1);
			break;
		default:
			ft_printf("NODE_UNKNOWN\n");
			break;
	}
}

void	ft_parser_test(t_token *tokens)
{
	t_parser_node *root;

	if (!tokens)
	{
		ft_printf("No tokens provided to parser test.\n");
		return;
	}
	root = ft_parser(tokens);
	ft_printf("--- Parser AST ---\n");
	print_parser_node(root, 0);
	ft_printf("--- End AST ---\n");
	ft_parser_free(root);
}