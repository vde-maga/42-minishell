// Inspired by: YT video id AqyZztKlSGQ

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOKEN_WORD,			// Regular words/commands/arguments
	TOKEN_PIPE,			// |
	TOKEN_OR,			// ||
	TOKEN_AND_IF,		// &&
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
	char			quote;       // 0 = none, '\'' = single, '"' = double 
    int				was_quoted;  // 1 if the entire token was wrapped by quotes
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


// lexer_free.c
void	ft_lexer_free(t_lexer *lexer);
void	ft_token_free(t_token *token);
void	ft_tokens_free(t_token *tokens);

// lexer_utils.c
void	ft_lexer_skip_spaces(t_lexer *lexer);
void	ft_lexer_advance(t_lexer *lexer);
void	print_tokens(t_token *tokens);

// lexer.c
void	ft_add_token(t_lexer *lexer, t_token_type type, char *value);
int	ft_lexer(char *input);

// lexer_tokenizer.c
int	ft_lexer_tokenize(t_lexer *lexer);

// lexer_tokenizer_utils.c
void    ft_lex_add_single_operator(t_lexer *lexer, char current);
void    ft_lex_add_double_operator(t_lexer *lexer, char current, char next);
void    ft_tok_check_quoted(t_token *new_token);
#endif