/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:20 by ruiferna          #+#    #+#             */
/*   Updated: 2025/09/08 15:17:39 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_init_vars(t_minishell *ms_data)
{
    ms_data->env = NULL;
    ms_data->exit_status = -1;
}

int main(int ac, char **av, char **envp)
{
    t_minishell ms_data;
    char *str_readline;
    char *line;

    (void)ac;
    (void)av;
    (void)envp;
    ft_init_vars(&ms_data);
    while (1)
    {
        str_readline = get_str_readline();
        line = readline(str_readline);
        free(str_readline);
        if (!line)
            break;
        if (ft_strncmp(line, "exit", 5) == 0)
        {
            free(line);
            exit(130);
        }
        if (ft_strncmp(line, "\0", 1))
        {
            // TODO: Add logic to add the used command to the history and to really execute the command
            break;
        }
        free(line);
    }
    return 0;
}
