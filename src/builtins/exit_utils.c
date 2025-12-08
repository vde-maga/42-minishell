/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:53 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:28:54 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_quotes_from_arg(char *arg)
{
	char	*processed;
	int		i;
	int		j;

	processed = malloc(ft_strlen(arg) + 1);
	if (!processed)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] != '"' && arg[i] != '\'')
			processed[j++] = arg[i];
		i++;
	}
	processed[j] = '\0';
	return (processed);
}

int	ft_check_if_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_properly_quoted(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len <= 2)
		return (0);
	if (arg[0] != '"' && arg[0] != '\'')
		return (0);
	if (arg[len - 1] != '"' && arg[len - 1] != '\'')
		return (0);
	return (1);
}

// This function is now implemented in utils/string_utils.c
// as ft_count_array_elements
