#include "parser.h"
#include "minishell.h"

/*
 * FUNCTION: ft_parse_command
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Parses a simple command without pipes or logical operators
 *
 * PARAMETERS
 *   @tokens: Token list representing a simple command
 *
 * RETURN VALUE
 *   Pointer to new command node, or NULL on allocation failure
 *
 * NOTES
 *   - Creates NODE_CMD type parser node
 *   - Allocates and populates command data structure
 *   - Handles memory cleanup on failure
 * ─────────────────────────────────────────────────────────────────────────
 */
t_parser_node	*ft_parse_command(t_token *tokens)
{
	t_parser_node	*node;
	t_cmd_node		*cmd_data;

	if (!tokens)
		return (NULL);
	node = ft_parser_new_node(NODE_CMD);
	if (!node)
		return (NULL);
	cmd_data = ft_calloc(1, sizeof(t_cmd_node));
	if (!cmd_data)
	{
		free(node);
		return (NULL);
	}
	node->cmd_data = cmd_data;
	if (ft_populate_cmd_data(cmd_data, tokens) != 0)
	{
		ft_parser_free(node);
		return (NULL);
	}
	return (node);
}

/*
 * FUNCTION: ft_populate_cmd_data
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Fills the t_cmd_node with arguments and redirection data
 *
 * PARAMETERS
 *   @cmd: Command node to populate with data
 *   @toks: Token list containing command arguments and redirects
 *
 * RETURN VALUE
 *   0 on success, 1 on failure
 *
 * NOTES
 *   - Initializes command arguments array
 *   - Processes token list to extract args and redirects
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_populate_cmd_data(t_cmd_node *cmd, t_token *toks)
{
	if (init_cmd_args(cmd, toks) != 0)
		return (1);
	if (process_token_list(cmd, toks) != 0)
		return (1);
	return (0);
}

/*
 * FUNCTION: ft_handle_word_token
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handles a single word token by duplicating it and adding to args array
 *
 * PARAMETERS
 *   @cmd: Command node containing args array
 *   @i: Pointer to current index in args array
 *   @value: String value to duplicate and add to args
 *
 * RETURN VALUE
 *   0 on success, 1 on memory allocation failure
 *
 * NOTES
 *   - Duplicates string value using ft_strdup
 *   - Updates args array index on success
 *   - Cleans up args array on failure
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_handle_word_token(t_cmd_node *cmd, int *i, char *value)
{
	if (!cmd->args || !value)
		return (0);
	cmd->args[*i] = ft_strdup(value);
	if (!cmd->args[*i])
	{
		ft_free_str_arrays(cmd->args);
		cmd->args = NULL;
		return (1);
	}
	(*i)++;
	return (0);
}

/*
 * FUNCTION: ft_parser_count_args
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Counts how many WORD tokens are in a list, skipping redirections
 *
 * PARAMETERS
 *   @tokens: Token list to analyze
 *
 * RETURN VALUE
 *   Number of WORD tokens found
 *
 * NOTES
 *   - Skips redirection tokens and their associated filenames
 *   - Only counts actual command arguments
 *   - Handles NULL token values safely
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_parser_count_args(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->value)
			count++;
		else if (current->type >= TOKEN_REDIRECT_IN
			&& current->type <= TOKEN_HEREDOC)
		{
			if (current->next)
				current = current->next;
			else
				break ;
		}
		current = current->next;
	}
	return (count);
}

/*
 * FUNCTION: ft_parser_new_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Allocates and initializes a new parser node of specified type
 *
 * PARAMETERS
 *   @type: Node type (NODE_CMD, NODE_PIPE, NODE_AND, etc.)
 *
 * RETURN VALUE
 *   Pointer to new parser node, or NULL on allocation failure
 *
 * NOTES
 *   - Zero-initializes all node fields
 *   - Caller responsible for filling node-specific data
 *   - Memory must be freed by caller using ft_parser_free
 * ─────────────────────────────────────────────────────────────────────────
 */
t_parser_node	*ft_parser_new_node(t_node_type type)
{
	t_parser_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_parser_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}
