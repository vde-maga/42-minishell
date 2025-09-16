#include "minishell.h"

/* TODO: Improve `ft_heredoc` to be able to differ if delimiter was/wasn`t quoted

int ft_heredoc(t_minishell *ms_data, char *delimiter, int quoted)
*/

int ft_heredoc(t_minishell *ms_data, char *delimiter)
{
    int fds[2]; // TODO: Put this fds in the main struct??
    char *line;

    (void)ms_data; // expander não implementado ainda

    delimiter = ft_strip_quotes_local(delimiter);
    if (pipe(fds) < 0)
        return (free(delimiter), -1);
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fds[1]);
        free(line);
    }
    free(delimiter);
    if (close(fds[1]) < 0)
        return (close(fds[0]), -1);
    return fds[0];
}
