/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:37 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:48:56 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_exit_code
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Thread-safe getter/setter for the global exit code using
 *   atomic operations for signal safety
 *
 * PARAMETERS
 *   @value: Exit code to set, or -1 to retrieve current value
 *
 * RETURN VALUE
 *   Current exit code (when value == -1) or newly set code
 *
 * NOTES
 *   - Uses sig_atomic_t for signal-safe atomic operations
 *   - Static variable maintains global state across function calls
 *   - Value of -1 used as getter mode, any other value sets the code
 *   - Critical for propagating exit status across process boundaries
 *   - Signal safety: can be safely called from signal handlers
 *   - Volatile keyword prevents compiler optimizations
 * ─────────────────────────────────────────────────────────────────────────
 */
sig_atomic_t	ft_exit_code(int value)
{
	static volatile sig_atomic_t	code = 0;

	if (value == -1)
		return (code);
	code = value;
	return (code);
}
