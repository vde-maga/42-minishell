#include "minishell.h"

static char	*ft_expand_heredoc_line(t_minishell *ms_data, char *line)
{
	char	*expanded;
	t_token	temp_token;

	if (!line || !ms_data)
		return (line);
	temp_token.value = line;
	temp_token.type = TOKEN_WORD;
	temp_token.quote = '"';
	temp_token.was_quoted = 0;
	temp_token.next = NULL;
	if (ft_expand_variables(ms_data, ms_data->env_list) == -1)
		return (line);
	expanded = ft_strdup(temp_token.value);
	return (expanded);
}

int	ft_heredoc(t_minishell *ms_data, char *delimiter, int was_quoted)
{
	char	*line;
	char	*clean_delim;
	int		pipefd[2];

	clean_delim = ft_remove_quotes(delimiter);
	if (!clean_delim)
		return (-1);
	if (pipe(pipefd) < 0)
		return (free(clean_delim), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_printf("minishell: warning: heredoc delimited by EOF (wanted `%s')\n", clean_delim);
			break ;
		}
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		if (!was_quoted)
			line = ft_expand_heredoc_line(ms_data, line);
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
			redir->fd = ft_heredoc(ms_data, redir->filename, 0);
			if (redir->fd < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
