/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:37:28 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:37:29 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard.h"

static int	ft_is_wildcard(char c)
{
	return (c == '*');
}

int	ft_has_unquoted_wildcards(const char *str)
{
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (ft_is_wildcard(str[i]) && !in_single && !in_double)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_wildcard_match_recursive(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		if (ft_wildcard_match_recursive(pattern + 1, str))
			return (1);
		if (*str != '\0')
			return (ft_wildcard_match_recursive(pattern, str + 1));
		return (0);
	}
	if (*pattern != *str)
		return (0);
	return (ft_wildcard_match_recursive(pattern + 1, str + 1));
}

int	ft_wildcard_match(const char *pattern, const char *str)
{
	return (ft_wildcard_match_recursive(pattern, str));
}
