/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:45 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:38 by vde-maga         ###   ########.fr       */
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
