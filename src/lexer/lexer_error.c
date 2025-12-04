#include "../includes/minishell.h"

void	handle_bad_token(t_token *bad_token)
{
	if (bad_token->type == TOKEN_EOF)
		ft_print_syntax_error("newline");
	else if (bad_token->value && bad_token->value[0])
		ft_print_syntax_error(bad_token->value);
	else if (bad_token->type == TOKEN_PIPE)
		ft_print_syntax_error("|");
	else if (bad_token->type == TOKEN_OR)
		ft_print_syntax_error("||");
	else if (bad_token->type == TOKEN_REDIRECT_IN)
		ft_print_syntax_error("<");
	else if (bad_token->type == TOKEN_REDIRECT_OUT)
		ft_print_syntax_error(">");
	else if (bad_token->type == TOKEN_APPEND)
		ft_print_syntax_error(">>");
	else if (bad_token->type == TOKEN_HEREDOC)
		ft_print_syntax_error("<<");
	else if (bad_token->type == TOKEN_AND)
		ft_print_syntax_error("&");
	else if (bad_token->type == TOKEN_AND_IF)
		ft_print_syntax_error("&&");
	else if (bad_token->type == TOKEN_LPAREN)
		ft_print_syntax_error("(");
	else if (bad_token->type == TOKEN_RPAREN)
		ft_print_syntax_error(")");
	else
		ft_print_syntax_error("");
}
