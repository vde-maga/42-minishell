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
	free(clean_delim);
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

int	ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted)
{
	char	*line;
	char	*clean_delim;
	int		pipefd[2];

	// TODO: implement signal handling to heredocs
	clean_delim = ft_remove_quotes(delimiter);
	if (!clean_delim || pipe(pipefd) < 0)
		return (free(clean_delim), -1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (ft_heredoc_error(clean_delim), close(pipefd[0]),
				close(pipefd[1]), -1);
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		line = ft_process_heredoc_line(ms_data, line, was_quoted);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
	free(clean_delim);
	close(pipefd[1]);
	return (pipefd[0]);
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
			redir->fd = ft_heredoc(ms_data, redir->filename,
					redir->was_quoted);
			if (redir->fd < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
