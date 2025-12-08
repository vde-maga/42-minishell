/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:14 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:29:15 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: is_valid_identifier
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Validate if a string is a valid shell variable identifier
 *
 * PARAMETERS
 *   @str: String to validate
 *
 * RETURN VALUE
 *   1 if valid identifier, 0 if invalid
 *
 * NOTES
 *   - Valid identifiers start with letter or underscore
 *   - Subsequent characters can be alphanumeric or underscore
 *   - Empty strings are invalid
 *   - Follows POSIX shell identifier rules
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * FUNCTION: ft_builtin_unset
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Remove environment variables from the shell's environment
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing environment list
 *   @args: Array of variable names to remove
 *
 * RETURN VALUE
 *   0 on success, 1 if msdata is NULL, 2 for invalid options
 *
 * NOTES
 *   - Validates each variable name before removal
 *   - Silently ignores invalid identifiers
 *   - Rejects options starting with '-' (except empty string)
 *   - Continues processing remaining arguments even if some fail
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_builtin_unset(t_minishell *msdata, char **args)
{
	int	i;

	if (!msdata)
		return (1);
	if (!args || !args[1])
		return (0);
	if (args[1][0] == '-' && args[1][1] != '\0')
	{
		ft_putstr_fd("minishell: unset: -", 2);
		ft_putchar_fd(args[1][1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			ft_unset_env_var(&msdata->env_list, args[i]);
		i++;
	}
	return (0);
}
