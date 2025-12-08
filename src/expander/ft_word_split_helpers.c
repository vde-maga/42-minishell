/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:55 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:56 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

/*
 * FUNCTION: ft_new_word_token
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Create a new word token from a string
 *
 * PARAMETERS
 *   @word: String value for the token
 *   @out: Pointer to store created token
 *
 * RETURN VALUE
 *   0 on success, -1 on memory allocation failure
 *
 * NOTES
 *   - Creates TOKEN_WORD type with duplicated string value
 *   - Sets was_quoted to 0 and next to NULL
 *   - Memory allocation responsibility: caller owns created token
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_new_word_token(const char *word, t_token **out)
{
	t_token	*tmp;

	tmp = ft_calloc(1, sizeof(t_token));
	if (!tmp)
		return (-1);
	tmp->type = TOKEN_WORD;
	tmp->value = ft_strdup(word);
	if (!tmp->value)
	{
		free(tmp);
		return (-1);
	}
	tmp->was_quoted = 0;
	tmp->next = NULL;
	*out = tmp;
	return (0);
}

/*
 * FUNCTION: ft_build_token_chain
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Build a linked list of word tokens from an array of words
 *
 * PARAMETERS
 *   @words: Array of word strings to convert to tokens
 *   @last_out: Pointer to store last token in chain (optional)
 *
 * RETURN VALUE
 *   Pointer to first token in chain, or NULL on error
 *
 * NOTES
 *   - Creates TOKEN_WORD type tokens for each word
 *   - Sets was_quoted to 0 for all tokens
 *   - Memory allocation responsibility: caller owns token chain
 * ─────────────────────────────────────────────────────────────────────────
 */
t_token	*ft_build_token_chain(char **words, t_token **last_out)
{
	int		i;
	t_token	*first;
	t_token	*last;
	t_token	*tmp;

	i = 0;
	first = NULL;
	last = NULL;
	while (words[i])
	{
		if (ft_new_word_token(words[i], &tmp) < 0)
			return (NULL);
		if (i == 0)
			first = tmp;
		else
			last->next = tmp;
		last = tmp;
		i++;
	}
	if (last_out)
		*last_out = last;
	return (first);
}

/*
 * FUNCTION: ft_link_chain_head
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Link a new token chain into the existing token list
 *
 * PARAMETERS
 *   @head: Pointer to token list head
 *   @prev: Previous token in list (NULL if inserting at head)
 *   @first_new: First token of new chain to link
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Updates head pointer if inserting at beginning
 *   - Updates prev->next if inserting after existing token
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_link_chain_head(t_token **head, t_token *prev, t_token *first_new)
{
	if (prev)
		prev->next = first_new;
	else
		*head = first_new;
}

/*
 * FUNCTION: ft_attach_tail_and_free
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Connect new chain tail to next token and free replaced token
 *
 * PARAMETERS
 *   @last: Last token of new chain
 *   @current: Token being replaced (to be freed)
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Links last token to current->next to maintain list continuity
 *   - Frees the replaced token's value and structure
 * - Memory allocation responsibility: function frees current token
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_attach_tail_and_free(t_token *last, t_token *current)
{
	if (last)
		last->next = current->next;
	free(current->value);
	free(current);
}
