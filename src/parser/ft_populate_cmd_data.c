/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_populate_cmd_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:34:25 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:48:47 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_cmd_args(t_cmd_node *cmd, t_token *toks)
{
	int	args_count;

	args_count = ft_parser_count_args(toks);
	if (args_count > 0)
	{
		cmd->args = ft_calloc(args_count + 1, sizeof(char *));
		if (!cmd->args)
			return (1);
	}
	return (0);
}

int	process_token_list(t_cmd_node *cmd, t_token *toks)
{
	t_token	*curr;
	int		i;

	i = 0;
	curr = toks;
	while (curr)
	{
		if (curr->type >= TOKEN_REDIRECT_IN && curr->type <= TOKEN_HEREDOC)
		{
			ft_parser_add_redirect(cmd, curr);
			if (curr->next)
				curr = curr->next;
		}
		else if (curr->type == TOKEN_WORD)
		{
			if (ft_handle_word_token(cmd, &i, curr->value) != 0)
				return (1);
		}
		if (curr)
			curr = curr->next;
	}
	return (0);
}
