#include "minishell.h"

static char	*ft_expand_heredoc_line(t_minishell *ms_data, char *line)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (ft_is_var_char(line[i], line[i + 1]))
			result = ft_append_var(ms_data, result, line, &i);
		else
		{
			result = ft_append_char(result, line[i]);
			i++;
		}
	}
	return (result);
}

static int	ft_heredoc_error(char *clean_delim)
{
	ft_printf("minishell: warning: heredoc delimited by EOF ");
	ft_printf("(wanted `%s')\n", clean_delim);
	//free(clean_delim);
	clean_delim = NULL;
	return (-1);
}

static char	*ft_process_heredoc_line(t_minishell *ms_data, char *line,
	int was_quoted)
{
	char	*expanded;

	if (!was_quoted)
	{
		expanded = ft_expand_heredoc_line(ms_data, line);
		free(line);
		return (expanded);
	}
	return (line);
}

static void	ft_heredoc_child(t_minishell *ms_data, char *clean_delim, int was_quoted, int *pipefd)
{
	char	*line;
	char	*temp;

	ft_signals_heredoc_signal();
	close(pipefd[0]);
	while (1)
	{
		write(STDERR_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			write(STDERR_FILENO, "\n", 1);
			ft_heredoc_error(clean_delim);
			break;
		}
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break;
		}
		temp = ft_strtrim(line, "\n");
		free(line);
		line = temp;
		line = ft_process_heredoc_line(ms_data, line, was_quoted);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	free(clean_delim);
	close(pipefd[1]);
	ft_free_shell(ms_data);
	exit(EXIT_SUCCESS);
}

static int	ft_heredoc_parent(pid_t pid, int *pipefd)
{
	int	status;
	int	exit_code;

	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_signal_handle_signals();
	ft_signals_heredoc_signal();
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 130)
		{
			ft_exit_code(130);
			close(pipefd[0]);
			return (-1);
		}
	}
	return (pipefd[0]);
}

int	ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted)
{
	char	*clean_delim;
	int	pipefd[2];
	pid_t	pid;

	clean_delim = ft_remove_quotes(delimiter);
	if (!clean_delim || pipe(pipefd) < 0)
		return (free(clean_delim), -1);
	pid = fork();
	if (pid < 0)
	{
		free(clean_delim);
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	if (pid == 0)
		ft_heredoc_child(ms_data, clean_delim, was_quoted, pipefd);
	free(clean_delim);
	return (ft_heredoc_parent(pid, pipefd));
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
			redir->fd = ft_heredoc(ms_data, redir->filename,
					redir->was_quoted);
			if (redir->fd < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
