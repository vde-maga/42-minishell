/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:45 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:31:46 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_escape(const char *s, int *i, char **res)
{
	(*i)++;
	if (s[*i])
		append_char_free(res, s[(*i)++]);
	else
		append_char_free(res, '\\');
}
