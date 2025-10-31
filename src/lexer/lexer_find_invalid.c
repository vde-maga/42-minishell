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
    int has_command;

    if (!tokens)
        return (NULL);
    current = tokens;
    if (ft_is_operator(current->type))
        return (current);
    if (ft_is_redirect(current->type))
        return (current);

    has_command = 0;
    while (current)
    {
        if (ft_is_operator(current->type))
        {
            if (!current->next)
                return (current); // Return the operator itself instead of sentinel
            if (ft_is_operator(current->next->type))
                return (current->next);
            if (current->next->type == TOKEN_EOF)
                return (current); // Return the operator itself
            has_command = 0; // Reset after operator
        }
        else if (ft_is_redirect(current->type))
        {
            if (!current->next)
                return (current); // Return the redirect itself
            if (current->next->type != TOKEN_WORD)
                return (current->next);
            if (!has_command)
                return (current); // Redirect without command
        }
        else if (current->type == TOKEN_WORD)
            has_command = 1;
        current = current->next;
    }
    return (NULL);
}
