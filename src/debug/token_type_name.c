/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:10 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:48 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	static const char	*names[] = {"TOKEN_WORD", "TOKEN_PIPE", "TOKEN_OR",
		"TOKEN_AND", "TOKEN_AND_IF", "in (<)", "out (>)", "force out (>|)",
		"append (>>)", "heredoc (<<)", "TOKEN_LPAREN", "TOKEN_RPAREN",
		"TOKEN_EOF", "TOKEN_ERROR"};

	if (type >= 0 && type <= TOKEN_ERROR)
		return (names[type]);
	return ("UNKNOWN");
}
