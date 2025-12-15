/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:32:11 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:59 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_heredoc_from_content
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates a pipe and writes pre-collected heredoc content to it
 *
 * PARAMETERS
 *   content: Pre-collected heredoc content to write to pipe
 *
 * RETURN VALUE
 *   Read end of pipe on success, -1 on error
 *
 * NOTES
 *   - Creates pipe for communication between processes
 *   - Writes content to write end of pipe
 *   - Closes write end and returns read end
 *   - Used when heredoc content is already collected
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_heredoc_from_content(char *content)
{
	int	pipefd[2];

	if (pipe(pipefd) < 0)
		return (-1);
	if (content)
		write(pipefd[1], content, ft_strlen(content));
	close(pipefd[1]);
	return (pipefd[0]);
}

/*
 * FUNCTION: ft_heredoc_parent
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Parent process handler for heredoc, waits for child and manages signals
 *
 * PARAMETERS
 *   pid: Process ID of child process
 *   pipefd: Array containing pipe file descriptors
 *
 * RETURN VALUE
 *   Read end of pipe on success, -1 on error or interruption
 *
 * NOTES
 *   - Closes write end of pipe to signal EOF to child
 *   - Ignores SIGINT while waiting for child
 *   - Restores signal handlers after child exits
 *   - Handles interruption (Ctrl+C) from child process
 *   - Returns appropriate file descriptor or error
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_heredoc_parent(pid_t pid, int *pipefd)
{
	int	status;
	int	exit_code;
	int	read_fd;

	close(pipefd[1]);
	pipefd[1] = -1;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	ft_signals_handle_signals();
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 130)
		{
			ft_exit_code(130);
			close(pipefd[0]);
			pipefd[0] = -1;
			return (-1);
		}
	}
	read_fd = pipefd[0];
	pipefd[0] = -1;
	return (read_fd);
}
