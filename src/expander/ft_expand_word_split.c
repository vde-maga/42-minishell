/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_word_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:50 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:51 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_free_word_array
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free an array of word strings
 *
 * PARAMETERS
 *   @words: Array of strings to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees each string in the array and the array itself
 *   - Handles NULL input gracefully
 * ─────────────────────────────────────────────────────────────────────────
 */
static void	ft_free_word_array(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

/*
 * FUNCTION: ft_replace_token_with_split
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Replace a single token with a chain of word tokens
 *
 * PARAMETERS
 *   @head: Pointer to token list head
 *   @prev: Previous token in list
 *   @current: Current token to replace
 *   @words: Array of words to create tokens from
 *
 * RETURN VALUE
 *   Pointer to last new token, or NULL on error
 *
 * NOTES
 *   - Builds token chain from words and links into list
 *   - Frees the original token after replacement
 *   - Memory allocation responsibility: modifies token list in place
 * ─────────────────────────────────────────────────────────────────────────
 */
static t_token	*ft_replace_token_with_split(t_token **head,
		t_token *prev, t_token *current, char **words)
{
	t_token	*first_new;
	t_token	*last;

	first_new = NULL;
	last = NULL;
	first_new = ft_build_token_chain(words, &last);
	if (!first_new || !last)
		return (NULL);
	ft_link_chain_head(head, prev, first_new);
	ft_attach_tail_and_free(last, current);
	return (last);
}

/*
 * FUNCTION: ft_apply_word_splitting
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Apply word splitting by replacing token with multiple word tokens
 *
 * PARAMETERS
 *   @head: Pointer to token list head
 *   @prev: Previous token in list
 *   @current: Current token to replace
 *   @words: Array of words to create tokens from
 *
 * RETURN VALUE
 *   1 on success, -1 on error
 *
 * NOTES
 *   - Removes current token and replaces with word tokens
 *   - Handles empty word arrays by removing token entirely
 *   - Memory allocation responsibility: modifies token list in place
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_apply_word_splitting(t_token **head, t_token *prev,
		t_token *current, char **words)
{
	t_token	*last;

	if (!words || !words[0])
	{
		if (prev)
			prev->next = current->next;
		else
			*head = current->next;
		free(current->value);
		free(current);
		return (1);
	}
	last = ft_replace_token_with_split(head, prev, current, words);
	if (!last)
		return (-1);
	ft_free_word_array(words);
	return (1);
}
