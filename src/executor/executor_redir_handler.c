#include "minishell.h"

static int	ft_handle_redirect_in(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (perror(redir->filename), -1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	return (0);
}

static int	ft_handle_redirect_out(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->filename), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	return (0);
}

static int	ft_handle_append(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->filename), -1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	return (0);
}

static int	ft_handle_heredoc(t_redir *redir)
{
	if (redir->fd < 0)
		return (0);
	if (dup2(redir->fd, STDIN_FILENO) < 0)
		return (close(redir->fd), perror("dup2"), -1);
	close(redir->fd);
	return (0);
}

int	ft_process_redir(t_redir *redir)
{
	if (redir->type == TOKEN_REDIRECT_IN)
		return (ft_handle_redirect_in(redir));
	else if (redir->type == TOKEN_REDIRECT_OUT)
		return (ft_handle_redirect_out(redir));
	else if (redir->type == TOKEN_APPEND)
		return (ft_handle_append(redir));
	else if (redir->type == TOKEN_HEREDOC)
		return (ft_handle_heredoc(redir));
	return (0);
}