/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
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

int	ft_should_match_hidden(const char *pattern)
{
	return (pattern[0] == '.');
}

char	*ft_extract_dir_path(const char *pattern)
{
	char	*last_slash;
	char	*dir_path;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup("."));
	if (last_slash == pattern)
		return (ft_strdup("/"));
	dir_path = ft_substr(pattern, 0, last_slash - pattern);
	return (dir_path);
}

char	*ft_extract_basename_pattern(const char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup(pattern));
	return (ft_strdup(last_slash + 1));
}
