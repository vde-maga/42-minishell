#include "../includes/minishell.h"

/*
 * FUNCTION: ft_lexer_free
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free lexer structure and its associated token list
 *
 * PARAMETERS
 *   @lexer: Lexer structure to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees token list before freeing lexer structure
 *   - Safely handles NULL input
 *   - Memory allocation responsibility: function manages lexer cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_lexer_free(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->tokens)
		ft_tokens_free(lexer->tokens);
	free(lexer);
}

// ft_token_free is now implemented as ft_free_token_node
// in utils/string_utils.c

/*
 * FUNCTION: ft_tokens_free
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free an entire token linked list
 *
 * PARAMETERS
 *   @tokens: Head of token list to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Uses generic linked list freer with token-specific cleanup
 *   - Safely handles NULL input
 *   - Memory allocation responsibility: function manages entire list cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_tokens_free(t_token *tokens)
{
	if (!tokens)
		return ;
	ft_free_linked_list(tokens, ft_free_token_node);
}
