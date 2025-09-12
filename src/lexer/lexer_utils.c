#include "../includes/minishell.h"

void	ft_lexer_skip_spaces(t_lexer *lexer)
{
	while (lexer->pos < lexer->len && lexer->input[lexer->pos] && 
		(lexer->input[lexer->pos] == ' ' || lexer->input[lexer->pos] == '\t'))
	{
		lexer->pos++;
		if (lexer->pos >= lexer->len)
			lexer->current_char = '\0';
		else
			lexer->current_char = lexer->input[lexer->pos];
	}
}

void ft_lexer_advance(t_lexer *lexer)
{
	lexer->pos++;
	if (lexer->pos >= lexer->len)
		lexer->current_char = '\0';
	else
		lexer->current_char = lexer->input[lexer->pos];
}

// TODO: Function to test lexing on main loop. Broken ATM
void	print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_str;

	current = tokens;
	ft_printf("=== TOKENS ===\n");
	while (current)
	{
		if (current->type == TOKEN_WORD)
			type_str = "WORD";
		else if (current->type == TOKEN_PIPE)
			type_str = "PIPE";
		else if (current->type == TOKEN_REDIRECT_IN)
			type_str = "REDIRECT_IN";
		else if (current->type == TOKEN_REDIRECT_OUT)
			type_str = "REDIRECT_OUT";
		else if (current->type == TOKEN_APPEND)
			type_str = "APPEND";
		else if (current->type == TOKEN_HEREDOC)
			type_str = "HEREDOC";
		else if (current->type == TOKEN_EOF)
			type_str = "EOF";
		else if (current->type == TOKEN_AND_IF)
			type_str = "AND_IF";
		else
			type_str = "ERROR";
		ft_printf("Type: %s, Value: %s\n", type_str, 
			current->value ? current->value : "NULL");
		current = current->next;
	}
	ft_printf("==============\n");
}