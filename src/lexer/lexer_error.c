#include "../includes/minishell.h"

static void	print_token_error(char *value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(value, 2);
	ft_putstr_fd("'\n", 2);
}

void	handle_bad_token(t_token *bad_token)
{
	if (bad_token->type == TOKEN_EOF)
		print_token_error("newline");
	else if (bad_token->value && bad_token->value[0])
		print_token_error(bad_token->value);
	else if (bad_token->type == TOKEN_PIPE)
		print_token_error("|");
	else if (bad_token->type == TOKEN_OR)
		print_token_error("||");
	else if (bad_token->type == TOKEN_REDIRECT_IN)
		print_token_error("<");
	else if (bad_token->type == TOKEN_REDIRECT_OUT)
		print_token_error(">");
	else if (bad_token->type == TOKEN_APPEND)
		print_token_error(">>");
	else if (bad_token->type == TOKEN_HEREDOC)
		print_token_error("<<");
	else if (bad_token->type == TOKEN_AND)
		print_token_error("&");
	else if (bad_token->type == TOKEN_AND_IF)
		print_token_error("&&");
	else if (bad_token->type == TOKEN_LPAREN)
		print_token_error("(");
	else if (bad_token->type == TOKEN_RPAREN)
		print_token_error(")");
	else
		print_token_error("");
}
