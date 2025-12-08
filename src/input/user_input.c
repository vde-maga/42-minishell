/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:32:40 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:32:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cleanup_gnl_buffer(int fd)
{
	char	*line;

	(void)fd;
	if (isatty(STDIN_FILENO))
		return ;
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		free(line);
	}
}

static void	get_str_non_interactive(t_minishell *ms_data, int type)
{
	char	*line;
	char	*trimmed;
	char	*old_ref;

	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		free(ms_data->input_line);
		ms_data->input_line = NULL;
		return ;
	}
	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (type == 2)
	{
		old_ref = ms_data->input_line;
		ms_data->input_line = ft_strjoin(old_ref, trimmed);
		free(old_ref);
		free(trimmed);
	}
	else
	{
		free(ms_data->input_line);
		ms_data->input_line = trimmed;
	}
}

/*
 * FUNCTION: get_str_readline
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Reads user input using readline library,
 *   handling both interactive and non-interactive modes
 *
 * PARAMETERS
 *   ms_data: Minishell data structure
 *   type: Input type (1 = new line, 2 = continuation line)
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Uses readline for interactive mode with history and editing
 *   - Falls back to get_next_line for non-interactive mode
 *   - Handles line continuation (type 2) by appending to existing input
 *   - Manages memory for input line properly
 * ─────────────────────────────────────────────────────────────────────────
 */
void	get_str_readline(t_minishell *ms_data, int type)
{
	char	prompt[PATH_MAX + 32];
	char	*old_ref;

	ft_usr_print_prompt_color(ms_data, type, prompt);
	if (!isatty(STDIN_FILENO))
	{
		get_str_non_interactive(ms_data, type);
		return ;
	}
	if (type == 2)
	{
		old_ref = ms_data->input_line;
		ms_data->input_line = ft_strjoin(old_ref, readline(prompt));
		free(old_ref);
	}
	else
	{
		free(ms_data->input_line);
		ms_data->input_line = readline(prompt);
	}
}
