#include "minishell.h"

static void	ft_heredoc_child_setup(t_minishell *ms_data, char *clean_delim,
	int *pipefd)
{
	ms_data->hdc_delim = clean_delim;
	shell_struct(ms_data, 0);
	ft_signals_heredoc_signal();
	close(pipefd[0]);
	pipefd[0] = -1;
}

static char	*ft_heredoc_read_line(char *clean_delim)
{
	char	*line;

	write(STDERR_FILENO, "heredoc> ", 9);
	line = ft_heredoc_readline(STDIN_FILENO);
	if (!line)
	{
		write(STDERR_FILENO, "\n", 1);
		ft_heredoc_error(clean_delim);
		return (NULL);
	}
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

static void	ft_heredoc_write_line(t_minishell *ms_data, char *line,
	int was_quoted, int write_fd)
{
	char	*temp;

	temp = ft_strtrim(line, "\n");
	free(line);
	line = temp;
	line = ft_process_heredoc_line(ms_data, line, was_quoted);
	ft_putendl_fd(line, write_fd);
	free(line);
}

static void	ft_heredoc_child_loop(t_minishell *ms_data, char *clean_delim,
	int was_quoted, int write_fd)
{
	char	*line;

	while (1)
	{
		line = ft_heredoc_read_line(clean_delim);
		if (!line)
			break ;
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		ft_heredoc_write_line(ms_data, line, was_quoted, write_fd);
	}
}

/*
 * FUNCTION: ft_heredoc_child
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Child process handler for heredoc input collection
 *
 * PARAMETERS
 *   ms_data: Minishell data structure
 *   clean_delim: Clean delimiter string (quotes removed)
 *   was_quoted: Flag indicating if delimiter was quoted
 *   pipefd: Array containing pipe file descriptors
 *
 * RETURN VALUE
 *   None (function exits child process)
 *
 * NOTES
 *   - Sets up heredoc-specific signal handlers
 *   - Reads input lines until delimiter is found
 *   - Processes variable expansion if delimiter was not quoted
 *   - Writes processed lines to pipe for parent process
 *   - Exits with success status after completion
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_heredoc_child(t_minishell *ms_data, char *clean_delim,
	int was_quoted, int *pipefd)
{
	ft_heredoc_child_setup(ms_data, clean_delim, pipefd);
	ft_heredoc_child_loop(ms_data, clean_delim, was_quoted, pipefd[1]);
	free(clean_delim);
	ms_data->hdc_delim = NULL;
	close(pipefd[1]);
	pipefd[1] = -1;
	ft_free_shell_child(ms_data);
	exit(EXIT_SUCCESS);
}
