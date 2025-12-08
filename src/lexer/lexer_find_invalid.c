/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_find_invalid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:32:53 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:32:54 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*ft_validate_token(t_token *current)
{
	t_token	*result;

	if (ft_is_operator(current->type))
	{
		result = ft_check_operator_validity(current);
		if (result)
			return (result);
	}
	else if (ft_is_redirect(current->type))
	{
		result = ft_check_redirect_validity(current);
		if (result)
			return (result);
	}
	return (NULL);
}

static t_token	*ft_check_syntax_edge(t_token *head)
{
	t_token	*cur;

	cur = head;
	if (ft_is_operator(cur->type) || cur->type == TOKEN_RPAREN)
		return (cur);
	while (cur)
	{
		if (cur->type == TOKEN_LPAREN && cur->next
			&& cur->next->type == TOKEN_RPAREN)
			return (cur);
		cur = cur->next;
	}
	return (head);
}

t_token	*ft_lexer_invalid_token(t_token *tokens)
{
	t_token	*cur;
	t_token	*res;

	if (!tokens)
		return (NULL);
	if (ft_lexer_valid(tokens) == -1)
		return (ft_check_syntax_edge(tokens));
	cur = tokens;
	if (ft_is_operator(cur->type))
		return (cur);
	while (cur)
	{
		res = ft_validate_token(cur);
		if (res)
			return (res);
		cur = cur->next;
	}
	return (NULL);
}
