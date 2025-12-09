/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:50 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:49:04 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

/*
 * FUNCTION: ft_free_linked_list
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Generic linked list freer with custom node cleanup function
 *
 * PARAMETERS
 *   @list: Pointer to linked list head
 *   @free_func: Function to free individual nodes
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Handles different list structures (token, redir, generic)
 *   - Uses function pointer for type-specific cleanup
 *   - Safely handles NULL inputs
 *   - Memory allocation responsibility: function manages entire list cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: ft_free_token_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free a single token node and its associated data
 *
 * PARAMETERS
 *   @token: Token node to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees token value and heredoc content if present
 *   - Safely handles NULL input
 *   - Used with ft_free_linked_list for token list cleanup
 *   - Memory allocation responsibility: function manages token cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: ft_free_redir_node
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free a single redirection node and its associated data
 *
 * PARAMETERS
 *   @redir: Redirection node to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees filename and heredoc content if present
 *   - Closes file descriptor if > 2 (not stdin/stdout/stderr)
 *   - Safely handles NULL input
 *   - Memory allocation responsibility: function manages redirection cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
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
