/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:32 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:33 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_var_name(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= 'a' && s[i] <= 'z')
				|| s[i] == '_'
				|| (i > 0 && (s[i] >= '0' && s[i] <= '9'))))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_special_param(char *s)
{
	if (!s || !*s)
		return (0);
	if ((s[0] == '?' || s[0] == '$') && s[1] == '\0')
		return (1);
	return (0);
}
