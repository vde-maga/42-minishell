#include "../includes/minishell.h"

static int	ft_is_operator(t_token_type type)
{
    return (type == TOKEN_PIPE || type == TOKEN_OR || type == TOKEN_AND
        || type == TOKEN_AND_IF);
}

static int	ft_is_redirect(t_token_type type)
{
    return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
        || type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

t_token	*ft_lexer_invalid_token(t_token *tokens)
{
    t_token *current;
    static t_token newline_sentinel = { .type = TOKEN_EOF, .value = NULL, .quote = 0, .was_quoted = 0, .next = NULL };

    if (!tokens)
        return (NULL);
    current = tokens;
    if (ft_is_operator(current->type))
        return (current);
    while (current)
    {
        if (ft_is_operator(current->type))
        {
            if (!current->next)
                return (&newline_sentinel);
            if (ft_is_operator(current->next->type))
                return (current->next);
            if (current->next->type == TOKEN_EOF)
                return (&newline_sentinel);
        }
        if (ft_is_redirect(current->type))
        {
            if (!current->next)
                return (&newline_sentinel);
            if (current->next->type != TOKEN_WORD)
                return (current->next);
        }
        current = current->next;
    }
    return (NULL);
}
