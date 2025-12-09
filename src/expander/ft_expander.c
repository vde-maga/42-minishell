/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:52 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:44 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_expander
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Main expansion engine that processes all token expansions
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing token list
 *   @env: Environment list for variable expansion
 *
 * RETURN VALUE
 *   Pointer to expanded token list, or NULL on error
 *
 * NOTES
 *   - Orchestrates variable, quote, and wildcard expansion
 *   - Returns NULL if no tokens exist or expansion fails
 *   - Memory allocation responsibility: caller owns returned token list
 * ─────────────────────────────────────────────────────────────────────────
 */
t_token	*ft_expander(t_minishell *msdata, t_env *env)
{
	if (!msdata->tokens)
		return (NULL);
	if (ft_expand_variables(msdata, env) == -1)
		return (NULL);
	return (msdata->tokens);
}
