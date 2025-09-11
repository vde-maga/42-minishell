#include "../includes/minishell.h"

void	ft_lexer_free(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->tokens)
		ft_tokens_free(lexer->tokens);
	free(lexer);
}

void	ft_token_free(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	ft_tokens_free(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		ft_token_free(current);
		current = next;
	}
}