/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:47:14 by ruiferna          #+#    #+#             */
/*   Updated: 2025/09/08 17:02:37 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_str_readline(void)
{
    char    *buffer;
    size_t  buffsize;
    char    cwd[BUFSIZ];

    buffer = NULL;
    ft_get_cwd(cwd, sizeof(cwd));
    ft_printf("minishell$> %s > ", cwd);
    if (getline(&buffer, &buffsize, stdin) == -1)
    {
        buffer = NULL;
        if (feof(stdin))
            // TODO: Need to remove the use of `feof` function.
            //       This if is triggered when you use Ctrl + D (for example)
            ft_printf("[EOF]");
        else
            ft_printf("getline func failed!");
    }
    return buffer;
}
