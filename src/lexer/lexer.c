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
	ft_tok_check_quoted(new_token);
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

int	ft_lexer(t_minishell *ms_data, char *input)
{
	/*
		TODO: Use the ms_data->tokens directly instead of returning/use the debug print function
		By doing this, I think we can rethink the need of the t_lexer struct, so we can
		possibly simplify the current code. Also, check the need of the ft_lexer_tokens function
	*/ 

	int		result;
	int		tok_res;

	ms_data->lexer = lexer_init(input);
	if (!ms_data->lexer)
		return (0);
	tok_res = ft_lexer_tokenize(ms_data->lexer); // returns 0 -> error/malloc err | 1 -> success | 2 -> unclosed quote
	if (tok_res == 0 || tok_res == 2)
	{
		ft_lexer_free(ms_data->lexer);
		ms_data->lexer = NULL;
		return (0);
	}
	result = ft_cmd_complete(ms_data->lexer->tokens);
	if (result)
		print_tokens(ms_data->lexer->tokens);
	// Transfer ownership of tokens to ms_data so main can use and free them.
	ms_data->tokens = ms_data->lexer->tokens;
	ms_data->lexer->tokens = NULL;
	ft_lexer_free(ms_data->lexer);
	ms_data->lexer = NULL;
	return (result);
}

// t_token *ft_lexer_tokens(char *input)
// {
//     t_lexer *lexer = lexer_init(input);
//     if (!lexer)
//         return (NULL);
//     int tok_res = ft_lexer_tokenize(lexer);
//     if (tok_res == 0 || tok_res == 2)
//         return (ft_lexer_free(lexer), NULL);
//     t_token *res = lexer->tokens;
//     lexer->tokens = NULL;
//     ft_lexer_free(lexer);
//     return (res);
// }
