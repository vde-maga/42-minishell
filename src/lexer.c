/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:56:17 by ruiferna          #+#    #+#             */
/*   Updated: 2025/09/08 18:29:41 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	if (!input)
		return (NULL);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->pos = 0;
	lexer->len = ft_strlen(input);
	lexer->current_char = input[0];
	lexer->tokens = NULL;
	return (lexer);
}

void	lexer_free(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->tokens)
		tokens_free(lexer->tokens);
	free(lexer);
}

void	token_free(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	tokens_free(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		token_free(current);
		current = next;
	}
}

// TODO: Function to test lexing on main loop. Broken ATM
void	print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_str;

	current = tokens;
	ft_printf("=== TOKENS ===\n");
	while (current)
	{
		if (current->type == TOKEN_WORD)
			type_str = "WORD";
		else if (current->type == TOKEN_PIPE)
			type_str = "PIPE";
		else if (current->type == TOKEN_REDIRECT_IN)
			type_str = "REDIRECT_IN";
		else if (current->type == TOKEN_REDIRECT_OUT)
			type_str = "REDIRECT_OUT";
		else if (current->type == TOKEN_APPEND)
			type_str = "APPEND";
		else if (current->type == TOKEN_HEREDOC)
			type_str = "HEREDOC";
		else if (current->type == TOKEN_EOF)
			type_str = "EOF";
		else
			type_str = "ERROR";
		ft_printf("Type: %s, Value: %s\n", type_str, 
			current->value ? current->value : "NULL");
		current = current->next;
	}
	ft_printf("==============\n");
}

