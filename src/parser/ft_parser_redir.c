#include "parser.h"

// Main function to add a redirection to a command node.
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

// Creates and populates a new redirection node from a token.
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
	new_redirect->next = NULL;
	return (new_redirect);
}

// Appends a new redirection node to the end of the list in cmd_data.
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
