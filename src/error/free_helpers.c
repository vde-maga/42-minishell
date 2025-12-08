/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:50 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:30:51 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * FUNCTION: ft_free_str_arrays
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free a NULL-terminated array of strings
 *
 * PARAMETERS
 *   @str: Array of strings to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees each string in the array and the array itself
 *   - Handles NULL input gracefully
 *   - Commonly used for freeing argv-style arrays
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_free_str_arrays(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

/*
 * FUNCTION: ft_free_shell_data
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free basic shell data structures (env array, input strings)
 *
 * PARAMETERS
 *   @ms_data: Minishell structure containing data to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees env array (not env_list), input_line, and input strings
 *   - Sets pointers to NULL after freeing to prevent double-free
 *   - Memory allocation responsibility: function manages its own cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_free_shell_data(t_minishell *ms_data)
{
	if (ms_data->env)
	{
		ft_free_str_arrays(ms_data->env);
		ms_data->env = NULL;
	}
	if (ms_data->input_line)
	{
		free(ms_data->input_line);
		ms_data->input_line = NULL;
	}
	if (ms_data->input)
	{
		free(ms_data->input);
		ms_data->input = NULL;
	}
}

/*
 * FUNCTION: ft_close_shell_fds
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Close all file descriptors used by the shell
 *
 * PARAMETERS
 *   @ms_data: Minishell structure containing file descriptors
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Closes heredoc pipe file descriptors and saved stdin/stdout
 *   - Only closes descriptors that are not -1 (invalid/unset)
 *   - Does not set descriptors to -1 after closing
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_close_shell_fds(t_minishell *ms_data)
{
	if (ms_data->hdc_fds[0] != -1)
		close(ms_data->hdc_fds[0]);
	if (ms_data->hdc_fds[1] != -1)
		close(ms_data->hdc_fds[1]);
	if (ms_data->saved_stdin != -1)
		close(ms_data->saved_stdin);
	if (ms_data->saved_stdout != -1)
		close(ms_data->saved_stdout);
}

/*
 * FUNCTION: ft_free_child_resources
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free resources specific to child processes (tokens, parser)
 *
 * PARAMETERS
 *   @ms_data: Minishell structure containing child resources
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees token list and parser AST tree
 *   - Used for child process cleanup to avoid parent resource conflicts
 *   - Does not set pointers to NULL after freeing
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_free_child_resources(t_minishell *ms_data)
{
	if (ms_data->tokens)
		ft_tokens_free(ms_data->tokens);
	if (ms_data->parser)
		ft_parser_free(ms_data->parser);
}
