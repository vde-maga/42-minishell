/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:37:37 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:49:23 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_line_ready(t_minishell *ms_data);

/*
 * FUNCTION: ft_line_ready
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Processes a complete line of input through expansion, parsing, and execution
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing tokens and parser
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Expands variables and wildcards in tokens
 *   - Parses tokens into abstract syntax tree
 *   - Executes the parsed command structure
 *   - Cleans up resources and adds to history
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_line_ready(t_minishell *ms_data)
{
	ft_expander(ms_data, ms_data->env_list);
	if (ms_data->tokens)
	{
		ms_data->parser = ft_parser(ms_data->tokens);
		if (ms_data->parser)
		{
			ft_executor(ms_data, ms_data->parser);
			ft_parser_free(ms_data->parser);
			ms_data->parser = NULL;
		}
		ft_tokens_free(ms_data->tokens);
		ms_data->tokens = NULL;
	}
	if (isatty(STDIN_FILENO))
		add_history(ms_data->input_line);
}
