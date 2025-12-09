/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:32:09 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:57 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_get_var_value
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Retrieves the value of a variable for heredoc expansion
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing environment variables
 *   var_name: Variable name string
 *   len: Length of variable name
 *
 * RETURN VALUE
 *   Newly allocated string with variable value
 *
 * NOTES
 *   - Handles special variables $? (exit code) and $$ (PID)
 *   - Looks up regular variables in environment list
 *   - Returns empty string for undefined variables
 *   - Caller is responsible for freeing the returned string
 * ─────────────────────────────────────────────────────────────────────────
 */
char	*ft_get_var_value(t_minishell *ms_data, char *var_name, int len)
{
	t_env	*env_node;
	char	*var_name_copy;
	char	*result;

	if (len == 1 && var_name[0] == '?')
		return (ft_itoa(ft_exit_code(-1)));
	if (len == 1 && var_name[0] == '$')
		return (ft_itoa(get_shell_pid_from_proc()));
	var_name_copy = ft_substr(var_name, 0, len);
	if (!var_name_copy)
		return (ft_strdup(""));
	env_node = ft_get_env_var(ms_data->env_list, var_name_copy);
	free(var_name_copy);
	if (env_node && env_node->value)
		result = ft_strdup(env_node->value);
	else
		result = ft_strdup("");
	return (result);
}

/*
 * FUNCTION: ft_expand_heredoc_line
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Expands variables in a heredoc line
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing environment variables
 *   line: Line to expand variables in
 *
 * RETURN VALUE
 *   Newly allocated string with expanded variables
 *
 * NOTES
 *   - Iterates through line character by character
 *   - Identifies and expands variable patterns
 *   - Preserves non-variable characters unchanged
 *   - Caller is responsible for freeing the returned string
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: ft_process_heredoc_line
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Processes a heredoc line, applying variable expansion if needed
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing environment variables
 *   line: Line to process
 *   was_quoted: Flag indicating if delimiter was quoted
 *
 * RETURN VALUE
 *   Processed line (may be original or newly allocated)
 *
 * NOTES
 *   - Only expands variables if delimiter was not quoted
 *   - Frees original line when expansion occurs
 *   - Returns original line unchanged when quoted
 *   - Caller is responsible for freeing the returned string
 * ─────────────────────────────────────────────────────────────────────────
 */
char	*ft_process_heredoc_line(t_minishell *ms_data, char *line,
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
