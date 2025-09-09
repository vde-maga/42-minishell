// Inspired by: YT video id AqyZztKlSGQ

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,			// Regular words/commands/arguments
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_EOF,			// \0
	TOKEN_ERROR			// Error token
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char		*input;
	int			pos;
	int			len;
	char		current_char;
	t_token		*tokens;
}	t_lexer;

t_lexer		*lexer_init(char *input);
void		lexer_free(t_lexer *lexer);
void		token_free(t_token *token);
void		tokens_free(t_token *tokens);
void		print_tokens(t_token *tokens);

#endif