#include "minishell.h"

int	ft_process_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIRECT_IN)
		return (ft_handle_redirect_in(redir));
	else if (redir->type == TOKEN_REDIRECT_OUT)
		return (ft_handle_redirect_out(redir));
	else if (redir->type == TOKEN_FORCE_REDIRECT_OUT)
		return (ft_handle_redirect_out(redir));
	else if (redir->type == TOKEN_APPEND)
		return (ft_handle_append(redir));
	else if (redir->type == TOKEN_HEREDOC)
		return (ft_handle_heredoc(redir));
	return (0);
}
