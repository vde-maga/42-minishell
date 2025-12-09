/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:08 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:08 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_helpers.h"
#include "minishell.h"

/*
 * FUNCTION: ft_handle_export_no_equal
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle export argument without '=' (variable name only)
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing environment list
 *   @arg: Variable name to export
 *
 * RETURN VALUE
 *   0 on success, 1 if invalid identifier
 *
 * NOTES
 *   - Validates identifier format before adding to environment
 *   - Sets variable with NULL value (exported but no value)
 *   - Error message printed to stderr for invalid identifiers
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_handle_export_no_equal(t_minishell *msdata, char *arg)
{
	if (!ft_is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (ft_set_env_var(&msdata->env_list, arg, NULL));
}

/*
 * FUNCTION: ft_handle_export_with_equal
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle export argument with '=' (variable assignment)
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing environment list
 *   @arg: Variable assignment string in format "name=value"
 *
 * RETURN VALUE
 *   0 on success, 1 on error (memory allocation or invalid identifier)
 *
 * NOTES
 *   - Extracts variable name and value from argument
 *   - Removes quotes from value before assignment
 *   - Frees allocated memory for var_name and value before returning
 *   - Memory allocation responsibility: function frees its own allocations
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_handle_export_with_equal(t_minishell *msdata, char *arg)
{
	char	*equal_sign;
	char	*var_name;
	char	*value;
	int		result;

	equal_sign = ft_strchr(arg, '=');
	var_name = ft_substr(arg, 0, equal_sign - arg);
	if (!var_name)
		return (1);
	if (!ft_is_valid_identifier(var_name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(var_name);
		return (1);
	}
	value = ft_remove_quotes(equal_sign + 1);
	result = ft_set_env_var(&msdata->env_list, var_name, value);
	free(value);
	free(var_name);
	return (result);
}

static int	ft_process_export_arg(t_minishell *msdata, char *arg)
{
	if (arg[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...]", 2);
		ft_putstr_fd(" or export -p\n", 2);
		return (2);
	}
	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (ft_handle_export_append(msdata, arg));
	if (!ft_strchr(arg, '='))
		return (ft_handle_export_no_equal(msdata, arg));
	return (ft_handle_export_with_equal(msdata, arg));
}

/*
 * FUNCTION: ft_builtin_export
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Set or export environment variables, or display all exported variables
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing environment list
 *   @args: Array of arguments where args[1+] are variables to export
 *
 * RETURN VALUE
 *   0 on success, non-zero on error (preserves last error status)
 *
 * NOTES
 *   - With no arguments, displays all exported variables in sorted order
 *   - Handles variable assignment with and without values
 *   - Supports append operation with "+=" syntax
 *   - Invalid identifiers cause error but processing continues for other args
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_builtin_export(t_minishell *msdata, char **args)
{
	int	status;
	int	final_status;
	int	i;

	if (!msdata || !args)
		return (1);
	if (!args[1] || !*args[1])
		return (ft_print_env_list(msdata));
	final_status = 0;
	i = 1;
	while (args[i])
	{
		status = ft_process_export_arg(msdata, args[i]);
		if (status != 0)
			final_status = status;
		i++;
	}
	return (final_status);
}
