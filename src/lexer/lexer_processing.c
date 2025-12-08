/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:32:58 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:32:59 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_bad_token(t_token *bad_token);

int	ft_cmd_complete(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE || current->type == TOKEN_AND_IF)
		return (0);
	if (current->type == TOKEN_WORD && (!current->value
			|| current->value[0] == '\0'))
		return (0);
	return (1);
}

/*
 * FUNCTION: process_lexer_result
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Processes lexer results, handles errors, and validates token sequence
 *
 * PARAMETERS
 *   ms: Minishell data structure containing lexer and tokens
 *   tok_res: Result code from tokenization process
 *
 * RETURN VALUE
 *   1 on success, 0 on general error, -1 on syntax error
 *
 * NOTES
 *   - Handles different error conditions from tokenization
 *   - Checks for invalid tokens and syntax errors
 *   - Cleans up lexer and tokens on error conditions
 *   - Sets appropriate exit codes for different error types
 * ─────────────────────────────────────────────────────────────────────────
 */
int	process_lexer_result(t_minishell *ms, int tok_res)
{
	t_token	*bad_token;

	if (tok_res == 0 || tok_res == 2)
	{
		ft_lexer_free(ms->lexer);
		ms->lexer = NULL;
		if (tok_res == 2)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			ft_exit_code(2);
			return (-1);
		}
		return (0);
	}
	bad_token = ft_lexer_invalid_token(ms->lexer->tokens);
	if (!bad_token)
		return (1);
	handle_bad_token(bad_token);
	ft_tokens_free(ms->lexer->tokens);
	ms->lexer->tokens = NULL;
	ft_lexer_free(ms->lexer);
	ms->lexer = NULL;
	ft_exit_code(2);
	return (-1);
}
