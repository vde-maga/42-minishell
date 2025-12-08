/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:18 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:34:19 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

// Recursively frees the entire parser node tree.
/*
 * FUNCTION: ft_parser_free
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Recursively free the entire parser AST tree
 *
 * PARAMETERS
 *   @node: Root node of parser tree to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Uses post-order traversal to free children before parent
 *   - Frees command data if present
 *   - Safely handles NULL input
 *   - Memory allocation responsibility: function manages entire tree cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_parser_free(t_parser_node *node)
{
	if (!node)
		return ;
	if (node->left)
		ft_parser_free(node->left);
	if (node->right)
		ft_parser_free(node->right);
	if (node->cmd_data)
		ft_parser_free_cmd_data(node->cmd_data);
	free(node);
}

// Frees the contents of a command node (args, redirections).
/*
 * FUNCTION: ft_parser_free_cmd_data
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free command node data including arguments and redirections
 *
 * PARAMETERS
 *   @cmd_data: Command node structure to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees argument array and redirection list
 *   - Safely handles NULL input
 *   - Memory allocation responsibility: function manages command data cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_parser_free_cmd_data(t_cmd_node *cmd_data)
{
	if (!cmd_data)
		return ;
	if (cmd_data->args)
		ft_free_str_arrays(cmd_data->args);
	if (cmd_data->redirs)
		free_redir_list(cmd_data->redirs);
	free(cmd_data);
}

/*
 * FUNCTION: free_redir_list
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free an entire redirection list
 *
 * PARAMETERS
 *   @list: Head of redirection list to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Uses generic linked list freer with redirection-specific cleanup
 *   - Safely handles NULL input
 *   - Memory allocation responsibility: function manages entire list cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	free_redir_list(t_redir *list)
{
	if (!list)
		return ;
	ft_free_linked_list(list, ft_free_redir_node);
}
