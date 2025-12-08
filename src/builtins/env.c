/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:44 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:28:45 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_builtin_env
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Display all environment variables with their values
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing environment list
 *   @args: Array of arguments (should be empty for env command)
 *
 * RETURN VALUE
 *   0 on success, 127 if arguments provided
 *
 * NOTES
 *   - Only displays variables that have values (has_value = true)
 *   - Prints in format "variable=value" one per line
 *   - Rejects any arguments (unlike some env implementations)
 *   - Preserves original order from environment list
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_builtin_env(t_minishell *msdata, char **args)
{
	t_env	*current;

	if (!msdata || !msdata->env_list)
		return (0);
	if (args && args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	current = msdata->env_list;
	while (current)
	{
		if (current->has_value)
			ft_printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
