#include "../includes/minishell.h"

static 	t_lexer	*lexer_init(char *input)
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

void	ft_add_token(t_lexer *lexer, t_token_type type, char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	if (!lexer->tokens)
	{
		lexer->tokens = new_token;
		return ;
	}
	current = lexer->tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	ft_lexer(char *input)
{
	t_lexer	lexer;

	lexer = *lexer_init(input);
	while (lexer.input[lexer.pos] != '\0')
	{
		ft_lexer_skip_spaces(&lexer);
		ft_printf("Current char: %c\n", lexer.input[lexer.pos]);
		if (lexer.input[lexer.pos] == '|')
			ft_add_token(&lexer, TOKEN_PIPE, NULL);
		else if (lexer.input[lexer.pos] == '<' && lexer.input[lexer.pos + 1] == '<')
		{
			ft_add_token(&lexer, TOKEN_HEREDOC, NULL);
			ft_lexer_advance(&lexer);
		}
		else if (lexer.input[lexer.pos] == '>' && lexer.input[lexer.pos + 1] == '>')
		{
			ft_add_token(&lexer, TOKEN_APPEND, NULL);
			ft_lexer_advance(&lexer);
		}
		else if (lexer.input[lexer.pos] == '&' && lexer.input[lexer.pos + 1] == '&')
		{
			ft_add_token(&lexer, TOKEN_AND_IF, NULL);
			ft_lexer_advance(&lexer);
		}
		else if (lexer.input[lexer.pos] == '<')
			ft_add_token(&lexer, TOKEN_REDIRECT_IN, NULL);
		else if (lexer.input[lexer.pos] == '>')
			ft_add_token(&lexer, TOKEN_REDIRECT_OUT, NULL);
		
		else if (lexer.input[lexer.pos] != '|' && lexer.input[lexer.pos] != '<' && lexer.input[lexer.pos] != '>')
		{
			int start_pos = lexer.pos;
			while (lexer.input[lexer.pos] && (lexer.input[lexer.pos] != ' ' && lexer.input[lexer.pos] != '\t') && lexer.input[lexer.pos] != '|' && lexer.current_char != '<' && lexer.current_char != '>')
				ft_lexer_advance(&lexer);
			int length = lexer.pos - start_pos;
			char *word = malloc(length + 1);
			if (!word)
				return ;
			ft_strlcpy(word, &lexer.input[start_pos], length + 1);
			ft_add_token(&lexer, TOKEN_WORD, word);
			continue;
		}
		else
			ft_add_token(&lexer, TOKEN_ERROR, NULL);
		ft_lexer_advance(&lexer);
	}
	print_tokens(lexer.tokens);
}
