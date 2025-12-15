/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_messages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:47 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:46:26 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_failure(t_minishell *ms_data, char *error)
{
	ft_free_shell(ms_data, 0);
	ft_putendl_fd(error, 2);
	exit(1);
}
