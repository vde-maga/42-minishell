/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:57 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:30:58 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "free_helpers.h"

/*
 * FUNCTION: ft_free_shell
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Comprehensive cleanup of all shell resources
 *
 * PARAMETERS
 *   @ms_data: Minishell structure containing all shell data
 *   @is_child: Flag indicating if this is a child process
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees shell data, closes file descriptors, cleans up get_next_line
 *   - Frees environment list and child-specific resources if applicable
 *   - Main cleanup function used during exit and error handling
 *   - Memory allocation responsibility: function manages all cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_free_shell(t_minishell *ms_data, int is_child)
{
	if (!ms_data)
		return ;
	ft_free_shell_data(ms_data);
	ft_close_shell_fds(ms_data);
	ft_cleanup_gnl_buffer(STDIN_FILENO);
	ft_free_env_list(ms_data->env_list);
	if (is_child)
		ft_free_child_resources(ms_data);
}

/*
 * FUNCTION: ft_free_shell_child
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Wrapper function to free shell resources for child processes
 *
 * PARAMETERS
 *   @ms_data: Minishell structure containing shell data
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Legacy wrapper for backward compatibility
 *   - Calls ft_free_shell with is_child = 1
 *   - Memory allocation responsibility: function manages all cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_free_shell_child(t_minishell *ms_data)
{
	ft_free_shell(ms_data, 1);
}
