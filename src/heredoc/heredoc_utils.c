#include "minishell.h"

// TODO: Remove this local temp functions
char	*ft_strip_quotes_local(char *s)
{
	if (!s)
		return NULL;
	size_t len = ft_strlen(s);
	if (len >= 2 && ((s[0] == '\'' && s[len - 1] == '\'') || (s[0] == '"' && s[len - 1] == '"')))
	{
		char *res = ft_substr(s, 1, len - 2);
		if (!res)
			ft_exit_failure(NULL, "ft_strip_quotes");
		return res;
	}
	return ft_strdup(s);
}

// TODO: Remove this temporary heredoc debug function
void ft_test_heredoc(t_minishell *ms)
{
    t_token *tokens = ms->tokens;
    if (!tokens)
        return;
    t_token *current = tokens;
    while (current)
    {
        if (current->type == TOKEN_HEREDOC)
        {
            if (current->next && current->next->type == TOKEN_WORD)
            {
                char *delim = current->next->value;
				// TODO: Improve `ft_heredoc` to be able to differ if delimiter was/wasn`t quoted 
                // int quoted = current->next->was_quoted;
                // int fd = ft_heredoc(ms, delim, quoted);
				int fd = ft_heredoc(ms, delim);
                if (fd >= 0)
                {
                    ft_printf("[heredoc] delimiter='%s' -> fd=%d\n", delim, fd);
                    close(fd);
                }
                else
                    ft_printf("[heredoc] delimiter='%s' -> interrupted/error\n", delim);
            }
            else
                ft_printf("[heredoc] missing delimiter token\n");
        }
        current = current->next;
    }
    ft_tokens_free(tokens);
}