#include "minishell.h"

void	process_escape(const char *s, int *i, char **res)
{
	(*i)++;
	if (s[*i])
		append_char_free(res, s[(*i)++]);
	else
		append_char_free(res, '\\');
}
