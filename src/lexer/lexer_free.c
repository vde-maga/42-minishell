#include "../includes/minishell.h"

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

void	ft_tokens_free(t_token *tokens)
{
	if (!tokens)
		return ;
	ft_free_linked_list(tokens, ft_free_token_node);
}
