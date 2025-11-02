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
	
	// Initialize token structure
	new_token->type = type;
	new_token->value = value;
	new_token->quote = 0;
	new_token->was_quoted = 0;
	new_token->next = NULL;
	
	// Check quote status
	ft_tok_check_quoted(new_token);
	
	// Add to token list
	if (!lexer->tokens)
	{
		lexer->tokens = new_token;
		return ;
	}
	
	current = lexer->tokens;
	while (current && current->next)
		current = current->next;
	
	if (current)
		current->next = new_token;
}

int	ft_cmd_complete(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	while (current->next)
		current = current->next;
	if (current->type == TOKEN_PIPE || current->type == TOKEN_AND_IF)
		return (0);
	if (current->type == TOKEN_WORD && (!current->value || current->value[0] == '\0'))
		return (0);
	return (1);
}

int	ft_lexer(t_minishell *ms_data, char *input)
{
	t_token	*bad_token;
	int		tok_res;

	ms_data->lexer = lexer_init(input);
	if (!ms_data->lexer)
		return (0);
	tok_res = ft_lexer_tokenize(ms_data->lexer);
	if (tok_res == 0 || tok_res == 2)
	{
		ft_lexer_free(ms_data->lexer);
		ms_data->lexer = NULL;
		if (tok_res == 2)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			ft_exit_code(2);
		}
		return (0);
	}
	bad_token = ft_lexer_invalid_token(ms_data->lexer->tokens);
	if (bad_token)
	{
		if (bad_token->type == TOKEN_EOF)
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		else
		{
			if (bad_token->value && bad_token->value[0])
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(bad_token->value, 2);
				ft_putstr_fd("'\n", 2);
			}
			else
			{
				if (bad_token->type == TOKEN_PIPE)
					ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				else if (bad_token->type == TOKEN_OR)
					ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
				else if (bad_token->type == TOKEN_REDIRECT_IN)
					ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
				else if (bad_token->type == TOKEN_REDIRECT_OUT)
					ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
				else if (bad_token->type == TOKEN_APPEND)
					ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
				else if (bad_token->type == TOKEN_HEREDOC)
					ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
				else if (bad_token->type == TOKEN_AND)
					ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
				else if (bad_token->type == TOKEN_AND_IF)
					ft_putstr_fd("minishell: syntax error near unexpected token `&&'\n", 2);
				else
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
					ft_putstr_fd(bad_token->value ? bad_token->value : "", 2);
					ft_putstr_fd("'\n", 2);
				}
			}
		}
		ft_tokens_free(ms_data->lexer->tokens);
		ms_data->lexer->tokens = NULL;
		ft_lexer_free(ms_data->lexer);
		ms_data->lexer = NULL;
		ft_exit_code(2);
		return (-1);
	}
	ms_data->tokens = ms_data->lexer->tokens;
	ms_data->lexer->tokens = NULL;
	ft_lexer_free(ms_data->lexer);
	ms_data->lexer = NULL;
	return (1);
}

