#include "minishell.h"
#include "lexer.h"
#include "parser.h"

void	ft_free_linked_list(void *list, void (*free_func)(void *))
{
	void	*current;
	void	*next;

	if (!list || !free_func)
		return ;
	current = list;
	while (current)
	{
		if (free_func == ft_free_token_node)
			next = ((t_token *)current)->next;
		else if (free_func == ft_free_redir_node)
			next = ((t_redir *)current)->next;
		else
			next = ((void **)current)[0];
		free_func(current);
		current = next;
	}
}

void	ft_free_token_node(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	if (!t)
		return ;
	if (t->value)
		free(t->value);
	if (t->heredoc_content)
		free(t->heredoc_content);
	free(t);
}

void	ft_free_redir_node(void *redir)
{
	t_redir	*r;

	r = (t_redir *)redir;
	if (!r)
		return ;
	if (r->filename)
		free(r->filename);
	if (r->heredoc_content)
		free(r->heredoc_content);
	if (r->fd > 2)
		close(r->fd);
	free(r);
}
