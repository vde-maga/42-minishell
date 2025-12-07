#include "minishell.h"

void	ft_close_heredoc_fds(t_cmd_node *cmd)
{
	t_redir	*redir;

	if (!cmd)
		return ;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC && redir->fd > 2)
		{
			close(redir->fd);
			redir->fd = -1;
		}
		redir = redir->next;
	}
}
