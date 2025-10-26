#include "minishell.h"

void ft_test_heredoc(t_minishell *ms)
{
    t_token *current = ms->tokens;
    if (!current)
        return;
    while (current)
    {
        if (current->type == TOKEN_HEREDOC)
        {
            if (current->next && current->next->type == TOKEN_WORD)
            {
                char *delim = current->next->value;
                int quoted = current->next->was_quoted;
                int fd = ft_heredoc(ms, delim, quoted);
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
    // ft_tokens_free(tokens);
}