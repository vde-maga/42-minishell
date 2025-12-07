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

/*
 * FUNCTION: ft_add_token
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates a new token with specified type and value, adds to lexer's token list
 *
 * PARAMETERS
 *   lexer: Lexer structure to which the token will be added
 *   type: Token type (operator, word, pipe, etc.)
 *   value: String value of the token (can be NULL for operators)
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Allocates memory for new token and initializes all fields
 *   - Handles memory cleanup if lexer is NULL or allocation fails
 *   - Sets quote and redirection fields to default values
 * ─────────────────────────────────────────────────────────────────────────
 */
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
	new_token->redir_fd = -1;
	new_token->heredoc_content = NULL;
	new_token->next = NULL;
	ft_tok_check_quoted(new_token);
	append_token(&lexer->tokens, new_token);
}

/*
 * FUNCTION: ft_lexer
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Main lexer function that tokenizes input string and processes tokens
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing lexer and tokens
 *   input: Raw input string to be tokenized
 *
 * RETURN VALUE
 *   1 on success, 0 or other values on error
 *
 * NOTES
 *   - Initializes lexer, tokenizes input, and processes results
 *   - Transfers ownership of tokens from lexer to ms_data
 *   - Cleans up lexer structure after processing
 * ─────────────────────────────────────────────────────────────────────────
 */
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
