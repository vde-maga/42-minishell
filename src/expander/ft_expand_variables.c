/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:48 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:40 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "lexer.h"

/*
 * FUNCTION: ft_should_apply_word_split
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Determine if word splitting should be applied to a token
 *
 * PARAMETERS
 *   @current: Token to check for word splitting
 *   @var_expanded: Status of variable expansion (2 = variable was expanded)
 *
 * RETURN VALUE
 *   1 if word splitting should be applied, 0 if not
 *
 * NOTES
 *   - Only applies if variable expansion occurred (var_expanded == 2)
 *   - Checks for whitespace characters in expanded value
 *   - Empty or NULL values also trigger word splitting
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_should_apply_word_split(t_token *current, int var_expanded)
{
	int	i;

	if (var_expanded != 2)
		return (0);
	if (!current->value)
		return (1);
	if (current->value[0] == '\0')
		return (1);
	i = 0;
	while (current->value[i])
	{
		if (current->value[i] == ' ' || current->value[i] == '\t'
			|| current->value[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
 * FUNCTION: ft_handle_word_split
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Apply word splitting to a token and update token list
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing token list
 *   @prev: Previous token in list
 *   @current: Current token to split
 *   @curr_ptr: Pointer to current token pointer (updated after split)
 *
 * RETURN VALUE
 *   1 on success, -1 on error
 *
 * NOTES
 *   - Splits token value into words and replaces token with word tokens
 *   - Updates curr_ptr to point to appropriate next token after split
 *   - Memory allocation responsibility: modifies token list in place
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_handle_word_split(t_minishell *msdata, t_token *prev,
			t_token *current, t_token **curr_ptr)
{
	char	**words;

	words = ft_word_split(current->value);
	if (ft_apply_word_splitting(&msdata->tokens, prev, current, words) < 0)
		return (-1);
	if (prev)
		*curr_ptr = prev->next;
	else
		*curr_ptr = msdata->tokens;
	return (1);
}

/*
 * FUNCTION: ft_expand_and_split_token
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Apply all expansion phases to a single token
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing token list
 *   @env: Environment list for variable lookup
 *   @prev_ptr: Pointer to previous token pointer
 *   @curr_ptr: Pointer to current token pointer
 *
 * RETURN VALUE
 *   0 on success, 1 if token list modified, -1 on error
 *
 * NOTES
 *   - Applies variable expansion, wildcard expansion, and word splitting
 *   - Updates prev_ptr and curr_ptr to handle list modifications
 *   - Memory allocation responsibility: modifies token list in place
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_expand_and_split_token(t_minishell *msdata, t_env *env,
			t_token **prev_ptr, t_token **curr_ptr)
{
	t_token	*current;
	t_token	*prev;
	int		var_expanded;

	current = *curr_ptr;
	prev = *prev_ptr;
	var_expanded = ft_process_token_expansion(msdata, env, prev, current);
	if (var_expanded < 0)
		return (-1);
	if (ft_expand_wildcards(&msdata->tokens, prev, current))
	{
		*curr_ptr = msdata->tokens;
		*prev_ptr = NULL;
		return (1);
	}
	if (ft_should_apply_word_split(current, var_expanded))
		return (ft_handle_word_split(msdata, prev, current, curr_ptr));
	*prev_ptr = current;
	*curr_ptr = current->next;
	return (var_expanded == 3);
}

/*
 * FUNCTION: ft_expand_variables
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Process all tokens for variable expansion, word splitting, and wildcards
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing token list
 *   @env: Environment list for variable lookup
 *
 * RETURN VALUE
 *   0 on success, -1 on error
 *
 * NOTES
 *   - Iterates through token list applying all expansion phases
 *   - Handles token list modifications during expansion
 *   - Memory allocation responsibility: modifies msdata->tokens in place
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_expand_variables(t_minishell *msdata, t_env *env)
{
	t_token	*current;
	t_token	*prev;
	int		result;

	if (!msdata || !env)
		return (-1);
	current = msdata->tokens;
	prev = NULL;
	while (current)
	{
		result = ft_expand_and_split_token(msdata, env, &prev, &current);
		if (result < 0)
			return (-1);
	}
	return (0);
}
