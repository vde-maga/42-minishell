#include "parser.h"

/*
 * FUNCTION: ft_parser_add_redirect
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Main function to add a redirection to a command node
 *
 * PARAMETERS
 *   @cmd_data: Command node to add redirection to
 *   @redirect_tok: Token representing the redirection operator
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Validates redirect token and filename token
 *   - Creates redirection node and appends to command's redirect list
 *   - Handles memory allocation failures gracefully
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_parser_add_redirect(t_cmd_node *cmd_data, t_token *redirect_tok)
{
	t_redir	*new_redirect;

	if (!cmd_data || !redirect_tok)
		return ;
	if (!redirect_tok->next || redirect_tok->next->type != TOKEN_WORD)
		return ;
	if (!redirect_tok->next->value)
		return ;
	new_redirect = create_redir_node(redirect_tok);
	if (!new_redirect)
		return ;
	append_redir_to_list(cmd_data, new_redirect);
}

/*
 * FUNCTION: create_redir_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates and populates a new redirection node from a token
 *
 * PARAMETERS
 *   @redir_tok: Token representing the redirection operator
 *
 * RETURN VALUE
 *   Pointer to new redirection node, or NULL on allocation failure
 *
 * NOTES
 *   - Extracts filename from next token in sequence
 *   - Handles heredoc content duplication if applicable
 *   - Initializes file descriptor to -1 (unassigned)
 *   - Memory must be freed by caller
 * ─────────────────────────────────────────────────────────────────────────
 */
t_redir	*create_redir_node(t_token *redir_tok)
{
	t_redir	*new_redirect;

	new_redirect = ft_calloc(1, sizeof(t_redir));
	if (!new_redirect)
		return (NULL);
	new_redirect->type = redir_tok->type;
	new_redirect->filename = ft_strdup(redir_tok->next->value);
	if (!new_redirect->filename)
	{
		free(new_redirect);
		return (NULL);
	}
	new_redirect->was_quoted = redir_tok->next->was_quoted;
	new_redirect->target_fd = redir_tok->redir_fd;
	new_redirect->fd = -1;
	new_redirect->next = NULL;
	if (redir_tok->type == TOKEN_HEREDOC && redir_tok->heredoc_content)
		new_redirect->heredoc_content = ft_strdup(redir_tok->heredoc_content);
	else
		new_redirect->heredoc_content = NULL;
	return (new_redirect);
}

/*
 * FUNCTION: append_redir_to_list
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Appends a new redirection node to the end of the list in cmd_data
 *
 * PARAMETERS
 *   @cmd_data: Command node containing redirection list
 *   @new_redirect: New redirection node to append
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Handles empty list case by setting head pointer
 *   - Traverses to end of list for non-empty cases
 *   - Maintains linked list structure integrity
 * ─────────────────────────────────────────────────────────────────────────
 */
void	append_redir_to_list(t_cmd_node *cmd_data, t_redir *new_redirect)
{
	t_redir	*last;

	if (!cmd_data->redirs)
		cmd_data->redirs = new_redirect;
	else
	{
		last = cmd_data->redirs;
		while (last && last->next)
			last = last->next;
		if (last)
			last->next = new_redirect;
	}
}
