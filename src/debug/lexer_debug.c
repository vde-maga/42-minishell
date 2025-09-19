#include "minishell.h"

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
		else if (current->type == TOKEN_OR)
			type_str = "OR";
		else
			type_str = "ERROR";
		if (current->type == TOKEN_WORD)
			ft_printf("Type: %s, Value: %s, Was Quoted?: %i, Quote: %c\n", type_str, 
				current->value ? current->value : "NULL", current->was_quoted, current->quote ? current->quote : '0');
		else
			ft_printf("Type: %s\n", type_str, 
					current->value ? current->value : "NULL");
		current = current->next;
	}
	ft_printf("==============\n");
}