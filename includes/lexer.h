// Inspired by: YT video id AqyZztKlSGQ

#ifndef LEXER_H
# define LEXER_H

typedef struct s_minishell	t_minishell;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_AND_IF,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_FORCE_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_ERROR
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			quote;
	int				was_quoted;
	int				redir_fd;
	char			*heredoc_content;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	int				pos;
	int				len;
	char			current_char;
	t_token			*tokens;
}					t_lexer;

// lexer_check_valid.c
int					ft_lexer_valid(t_token *tokens);
int					ft_is_operator(t_token_type type);
int					ft_is_redirect(t_token_type type);
t_token				*ft_check_operator_validity(t_token *current);
t_token				*ft_check_redirect_validity(t_token *current);

// lexer_free.c
void				ft_lexer_free(t_lexer *lexer);
void				ft_token_free(t_token *token);
void				ft_tokens_free(t_token *tokens);

// lexer_utils.c
void				ft_lexer_skip_spaces(t_lexer *lexer);
void				ft_lexer_advance(t_lexer *lexer);
t_token				*ft_lexer_invalid_token(t_token *tokens);

// lexer.c
void				ft_add_token(t_lexer *lexer, t_token_type type,
						char *value);
int					ft_lexer(t_minishell *ms_data, char *input);
t_token				*ft_lexer_tokens(char *input);

// lexer_tokenizer.c
int					ft_lexer_tokenize(t_lexer *lexer);

// lexer_tokenizer_utils.c
void				ft_lex_add_single_operator(t_lexer *lexer, char current);
void				ft_lex_add_double_operator(t_lexer *lexer, char current,
						char next);
void				ft_tok_check_quoted(t_token *new_token);

// lexer_processing.c
int					process_lexer_result(t_minishell *ms, int tok_res);
int					ft_cmd_complete(t_token *tokens);

#endif