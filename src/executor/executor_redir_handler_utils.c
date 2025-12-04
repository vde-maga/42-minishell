#include "minishell.h"

int	ft_get_redir_target_fd(t_redir *redir, int default_fd)
{
	if (redir->target_fd >= 0)
		return (redir->target_fd);
	return (default_fd);
}

int	ft_handle_redirect_in(t_redir *redir)
{
	int	fd;
	int	target;

	fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
		return (perror(redir->filename), -1);
	target = ft_get_redir_target_fd(redir, STDIN_FILENO);
	if (dup2(fd, target) < 0)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	return (0);
}

int	ft_handle_redirect_out(t_redir *redir)
{
	int	fd;
	int	target;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir->filename), -1);
	target = ft_get_redir_target_fd(redir, STDOUT_FILENO);
	if (dup2(fd, target) < 0)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	return (0);
}

int	ft_handle_append(t_redir *redir)
{
	int	fd;
	int	target;

	fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir->filename), -1);
	target = ft_get_redir_target_fd(redir, STDOUT_FILENO);
	if (dup2(fd, target) < 0)
		return (close(fd), perror("dup2"), -1);
	close(fd);
	return (0);
}

int	ft_handle_heredoc(t_redir *redir)
{
	if (redir->fd < 0)
		return (0);
	if (dup2(redir->fd, STDIN_FILENO) < 0)
	{
		close(redir->fd);
		redir->fd = -1;
		perror("dup2");
		return (-1);
	}
	close(redir->fd);
	redir->fd = -1;
	return (0);
}
