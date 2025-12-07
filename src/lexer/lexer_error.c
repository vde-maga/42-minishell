#include "../includes/minishell.h"

static void	print_token_error(const char *value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)value, 2);
	ft_putstr_fd("'\n", 2);
}

static const char	*get_token_str(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_OR)
		return ("||");
	if (type == TOKEN_REDIRECT_IN)
		return ("<");
	if (type == TOKEN_REDIRECT_OUT)
		return (">");
	if (type == TOKEN_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	if (type == TOKEN_AND)
		return ("&");
	if (type == TOKEN_AND_IF)
		return ("&&");
	if (type == TOKEN_LPAREN)
		return ("(");
	if (type == TOKEN_RPAREN)
		return (")");
	return ("");
}

void	handle_bad_token(t_token *bad_token)
{
	if (bad_token->type == TOKEN_EOF)
		ft_print_syntax_error("newline");
	else if (bad_token->value && bad_token->value[0])
		print_token_error(bad_token->value);
	else
		print_token_error(get_token_str(bad_token->type));
}
