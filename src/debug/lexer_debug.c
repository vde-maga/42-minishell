/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:42 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:29:43 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token_type_string(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	if (type == TOKEN_PIPE)
		return ("PIPE");
	if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == TOKEN_APPEND)
		return ("APPEND");
	if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	if (type == TOKEN_LPAREN)
		return ("LPAREN");
	if (type == TOKEN_RPAREN)
		return ("RPAREN");
	if (type == TOKEN_EOF)
		return ("EOF");
	if (type == TOKEN_AND_IF)
		return ("AND_IF");
	if (type == TOKEN_AND)
		return ("AND");
	if (type == TOKEN_OR)
		return ("OR");
	return ("ERROR");
}

static void	print_word_token(t_token *current, char *type_str)
{
	char	*value_str;
	char	quote_char;

	value_str = "NULL";
	if (current->value)
		value_str = current->value;
	quote_char = '0';
	if (current->quote)
		quote_char = current->quote;
	ft_printf("Type: %s, Value: %s, Was Quoted?: %i, Quote: %c\n",
		type_str, value_str, current->was_quoted, quote_char);
}

static void	print_non_word_token(char *type_str)
{
	ft_printf("Type: %s\n", type_str);
}

static void	print_single_token(t_token *current)
{
	char	*type_str;

	type_str = get_token_type_string(current->type);
	if (current->type == TOKEN_WORD)
		print_word_token(current, type_str);
	else
		print_non_word_token(type_str);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	ft_printf("=== TOKENS ===\n");
	while (current)
	{
		print_single_token(current);
		current = current->next;
	}
	ft_printf("==============\n");
}
