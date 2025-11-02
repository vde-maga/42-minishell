#include "minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	static const char	*names[] = {"TOKEN_WORD", "TOKEN_PIPE", "TOKEN_OR",
		"TOKEN_AND", "TOKEN_AND_IF", "in (<)", "out (>)", "append (>>)",
		"heredoc (<<)", "TOKEN_EOF", "TOKEN_ERROR"};

	if (type >= 0 && type <= TOKEN_ERROR)
		return (names[type]);
	return ("UNKNOWN");
}
