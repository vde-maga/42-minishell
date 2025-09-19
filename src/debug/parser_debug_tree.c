#include "minishell.h"

const char *token_type_names[] = {
    "TOKEN_WORD",
    "TOKEN_PIPE",
    "TOKEN_OR",
    "TOKEN_AND_IF",
    "in (<)",
    "out (>)",
    "append (>>)",
    "heredoc (<<)",
    "TOKEN_EOF",
    "TOKEN_ERROR"
};

static void	print_prefix(char *prefix)
{
    if (prefix && *prefix)
        ft_printf("%s", prefix);
}

static void	print_cmd_details(t_cmd_node *cmd)
{
    int i;

    if (!cmd)
        return;
    if (cmd->args)
    {
        i = 0;
        while (cmd->args[i])
        {
            ft_printf("%s", cmd->args[i]);
            if (cmd->args[i + 1])
                ft_printf(" ");
            i++;
        }
    }
    if (cmd->redirs)
    {
        t_redir *r = cmd->redirs;
        while (r)
        {
            ft_printf(" [redir type=%s file=%s]", token_type_names[r->type], r->filename);
            r = r->next;
        }
    }
}

/*
 * Recursive printer that draws ASCII tree using connectors.
 * prefix: accumulated printing prefix for current node
 * is_left: whether this node is a left child (affects connector)
 */
static void	print_parser_tree(t_parser_node *node, char *prefix, int is_left)
{
    char new_prefix[1024];
    char connector[16];

    if (!node)
    {
        print_prefix(prefix);
        ft_printf("(null)\n");
        return;
    }

    if (prefix == NULL)
        prefix = "";

    /* choose connector */
    if (is_left == 0)
        strcpy(connector, "");
    else if (is_left == 1)
        strcpy(connector, "├─ ");
    else
        strcpy(connector, "└─ ");

    print_prefix(prefix);
    ft_printf("%s", connector);
    /* print current node summary */
    if (node->type == NODE_CMD)
    {
        ft_printf("CMD: ");
        print_cmd_details(node->cmd_data);
        ft_printf("\n");
    }
    else if (node->type == NODE_PIPE)
        ft_printf("PIPE\n");
    else if (node->type == NODE_AND)
        ft_printf("AND\n");
    else if (node->type == NODE_OR)
        ft_printf("OR\n");
    else
        ft_printf("UNKNOWN\n");

    /* prepare prefix for children */
    if (node->left || node->right)
    {
        if (is_left == 0)
            strcpy(new_prefix, "");
        else if (is_left == 1)
            snprintf(new_prefix, sizeof(new_prefix), "%s│  ", prefix);
        else
            snprintf(new_prefix, sizeof(new_prefix), "%s   ", prefix);

        /* print left child (if present) */
        if (node->left)
        {
            print_parser_tree(node->left, new_prefix, 1);
        }
        else if (node->right)
        {
            /* indicate empty left branch */
            print_prefix(new_prefix);
            ft_printf("├─ (null)\n");
        }

        /* print right child */
        if (node->right)
        {
            /* for right child we need prefix where previous sibling uses space */
            char right_prefix[1024];
            if (is_left == 0)
                strcpy(right_prefix, "");
            else if (is_left == 1)
                snprintf(right_prefix, sizeof(right_prefix), "%s│  ", prefix);
            else
                snprintf(right_prefix, sizeof(right_prefix), "%s   ", prefix);
            print_parser_tree(node->right, right_prefix, 2);
        }
    }
}

void	ft_parser_tree_test(t_parser_node *root)
{
    // t_parser_node *root;

    // if (!tokens)
    // {
    //     ft_printf("No tokens provided to parser tree test.\n");
    //     return;
    // }
    // root = ft_parser(tokens);
    ft_printf("---------- Parser Debugger ------\n");
    print_parser_tree(root, "", 0);
    ft_printf("------- End Parser Debugger -----\n");
    // ft_parser_free(root);
}
