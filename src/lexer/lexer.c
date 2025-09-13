#include "../includes/minishell.h"

static 	t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	if (!input)
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	lexer->current_char = input[0];
	lexer->tokens = NULL;
	return (lexer);
}

void	ft_add_token(t_lexer *lexer, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	if (!lexer->tokens)
	{
		lexer->tokens = new_token;
		return ;
	}
	current = lexer->tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	ft_cmd_complete(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (0);
	current = tokens;
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE || current->type == TOKEN_AND_IF || current->type == TOKEN_OR)
		return (0);
	if (current->type == TOKEN_WORD && (!current->value || current->value[0] == '\0'))
		return (0);
	return (1);
}

int	ft_lexer(char *input)
{
	t_lexer	*lexer;
	int		result;

	lexer = lexer_init(input);
	if (!lexer)
		return (0);
	if (!ft_lexer_tokenize(lexer))
	{
		ft_lexer_free(lexer);
		return (0);
	}
	result = ft_cmd_complete(lexer->tokens);
	if (result)
		print_tokens(lexer->tokens);
	ft_lexer_free(lexer);
	return (result);
}
