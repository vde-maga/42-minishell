/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:20 by ruiferna          #+#    #+#             */
/*   Updated: 2025/09/08 16:55:57 by ruiferna         ###   ########.fr       */
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
    char *line;

    (void)ac;
    (void)av;
    (void)envp;
    ft_init_vars(&ms_data);
    while (1)
    {
        // TODO: 
        // 1 - Need to get line from user
        line = get_str_readline();
        ft_printf("%s\n", line);
        free(line);
        
        // 2 - Get as tokens (Lexing -> Parsing -> Evaluating)
        // 3 - Exec and repeat
    }
    return EXIT_SUCCESS;
}
