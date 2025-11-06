#include "../includes/minishell.h"

static t_lexer	*lexer_init(char *input)
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

static void	append_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current && current->next)
		current = current->next;
	current->next = new;
}

void	ft_add_token(t_lexer *lexer, t_token_type type, char *value)
{
	t_token	*new_token;

	if (!lexer)
	{
		if (value)
			free(value);
		return ;
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		if (value)
			free(value);
		return ;
	}
	new_token->type = type;
	new_token->value = value;
	new_token->quote = 0;
	new_token->was_quoted = 0;
	new_token->next = NULL;
	ft_tok_check_quoted(new_token);
	append_token(&lexer->tokens, new_token);
}

static int	process_lexer_result(t_minishell *ms, int tok_res);

int	ft_lexer(t_minishell *ms_data, char *input)
{
	int		tok_res;
	int		process_res;

	ms_data->lexer = lexer_init(input);
	if (!ms_data->lexer)
		return (0);
	tok_res = ft_lexer_tokenize(ms_data->lexer);
	process_res = process_lexer_result(ms_data, tok_res);
	if (process_res != 1)
		return (process_res);
	ms_data->tokens = ms_data->lexer->tokens;
	ms_data->lexer->tokens = NULL;
	ft_lexer_free(ms_data->lexer);
	ms_data->lexer = NULL;
	return (1);
}
