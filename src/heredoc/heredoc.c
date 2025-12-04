#include "minishell.h"

int	ft_heredoc_error(char *clean_delim)
{
	ft_putstr_fd("minishell: warning: heredoc delimited by EOF ", 2);
	ft_putstr_fd("(wanted `", 2);
	ft_putstr_fd(clean_delim, 2);
	ft_putstr_fd("')\n", 2);
	return (-1);
}

int	ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted)
{
	char	*clean_delim;
	pid_t	pid;

	clean_delim = ft_remove_quotes(delimiter);
	if (!clean_delim || pipe(ms_data->hdc_fds) < 0)
		return (free(clean_delim), -1);
	pid = fork();
	if (pid < 0)
	{
		free(clean_delim);
		close(ms_data->hdc_fds[0]);
		close(ms_data->hdc_fds[1]);
		return (-1);
	}
	if (pid == 0)
		ft_heredoc_child(ms_data, clean_delim, was_quoted, ms_data->hdc_fds);
	free(clean_delim);
	return (ft_heredoc_parent(pid, ms_data->hdc_fds));
}

int	ft_process_heredocs(t_minishell *ms_data, t_cmd_node *cmd)
{
	t_redir	*redir;

	if (!cmd)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (redir->fd > 2)
				close(redir->fd);
			if (redir->heredoc_content)
				redir->fd = ft_heredoc_from_content(redir->heredoc_content);
			else
				redir->fd = ft_heredoc(ms_data, redir->filename,
						redir->was_quoted);
			if (redir->fd < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
