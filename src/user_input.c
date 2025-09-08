/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:14 by ruiferna          #+#    #+#             */
/*   Updated: 2025/09/08 15:09:26 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_str_readline(void)
{
    char *input = "minishell$ ";
    char *str = malloc(sizeof(char) * (ft_strlen(input) + 1));
    if (!str)
        return NULL;
    strcpy(str, input);
    return str;
}
