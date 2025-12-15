/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:47 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:00 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_utils.h"

/*
 * FUNCTION: ft_handle_mixed_quotes_exit
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle exit argument with mixed or invalid quotes
 *
 * PARAMETERS
 *   @arg: Argument string potentially containing quotes
 *
 * RETURN VALUE
 *   Exit code (0-255) if valid numeric, -1 on error
 *
 * NOTES
 *   - Removes all quotes from argument before processing
 *   - Returns -1 for empty strings or non-numeric values
 *   - Frees allocated memory before returning
 *   - Memory allocation responsibility: function frees its own allocations
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_handle_mixed_quotes_exit(char *arg)
{
	char	*processed;
	int		is_valid_numeric;
	int		exit_code;

	processed = ft_remove_quotes_from_arg(arg);
	if (!processed)
		return (-1);
	if (processed[0] == '\0')
		return (free(processed), -1);
	is_valid_numeric = ft_check_if_numeric(processed);
	exit_code = -1;
	if (is_valid_numeric)
		exit_code = ft_atoi(processed) % 256;
	free(processed);
	return (exit_code);
}

/*
 * FUNCTION: ft_handle_quoted_exit
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle exit argument with properly matched quotes
 *
 * PARAMETERS
 *   @arg: Quoted argument string
 *
 * RETURN VALUE
 *   Exit code (0-255) if valid numeric, -1 on error
 *
 * NOTES
 *   - Expects properly matched opening and closing quotes
 *   - Removes outer quotes and validates inner content
 *   - Falls back to mixed quotes handler for invalid quote patterns
 *   - Memory allocation responsibility: function frees its own allocations
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_handle_quoted_exit(char *arg)
{
	char	*unquoted;
	int		len;
	int		is_valid_numeric;
	int		exit_code;

	if (!ft_is_properly_quoted(arg))
		return (ft_handle_mixed_quotes_exit(arg));
	len = ft_strlen(arg);
	unquoted = malloc(len - 1);
	if (!unquoted)
		return (-1);
	ft_strlcpy(unquoted, arg + 1, len - 1);
	is_valid_numeric = ft_check_if_numeric(unquoted);
	exit_code = -1;
	if (is_valid_numeric)
		exit_code = ft_atoi(unquoted) % 256;
	return (free(unquoted), exit_code);
}

/*
 * FUNCTION: ft_process_single_arg
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Process exit command with a single numeric argument
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing shell state
 *   @arg: Numeric exit code argument
 *
 * RETURN VALUE
 *   Does not return (calls exit())
 *
 * NOTES
 *   - Converts argument to long long and applies modulo 256
 *   - Frees all shell memory before exiting
 *   - This function never returns under normal operation
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_process_single_arg(t_minishell *msdata, char *arg)
{
	long long	exit_code;

	exit_code = ft_atoll(arg);
	ft_exit_free_and_exit(msdata, exit_code % 256);
	return (0);
}

/*
 * FUNCTION: ft_handle_no_args
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle exit command with no arguments
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing shell state
 *
 * RETURN VALUE
 *   Does not return (calls exit())
 *
 * NOTES
 *   - Uses the last command's exit code
 *   - Frees all shell memory before exiting
 *   - This function never returns under normal operation
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_handle_no_args(t_minishell *msdata)
{
	int	exit_code;

	exit_code = ft_exit_code(-1);
	ft_exit_free_and_exit(msdata, exit_code);
	return (0);
}
