#ifndef EXPANDER_H
# define EXPANDER_H

typedef struct s_expand_ctx
{
	t_env		*env;
	const char	*s;
	int			in_d;
	char		**res;
	int			*unquoted_expand;
}				t_expand_ctx;

typedef struct s_qctx
{
	const char	*s;
	char		*d;
	int			i;
	int			j;
	int			mode;
}				t_qctx;

t_token			*ft_expander(t_minishell *msdata, t_env *env);
int				ft_expand_variables(t_minishell *msdata, t_env *env);
char			*ft_remove_quotes(char *str);
int				ft_exp_replace_content(t_env *env, t_token *current,
					char *var_name);
int				ft_exp_special_param(t_minishell *msdata, t_token *current,
					char *var_name);
int				is_valid_env_var_name(char *str);
int				is_valid_special_param(char *str);
int				get_shell_pid_from_proc(void);
char			*ft_expand_variables_in_string(t_env *env, char *str,
					int *unquoted_expand);
char			*ft_strjoin_char(char *s1, char c);
char			*ft_get_variable_value(t_env *env, char *var_name);
char			**ft_word_split(char *str);
int				ft_apply_word_splitting(t_token **head, t_token *prev,
					t_token *current, char **words);
int				ft_process_token_expansion(t_minishell *msdata, t_env *env,
					t_token *current);

void			append_char_free(char **res, char c);
int				collect_or_special(const char *s, int j, char *name);
int				handle_dollar_ctx(t_expand_ctx *ctx, int i);
void			process_escape(const char *s, int *i, char **res);
void			expander_step(t_expand_ctx *ctx, int *i, int *in_s, int *in_d);

/* word split helpers */
t_token			*ft_build_token_chain(char **words, t_token **last_out);
void			ft_link_chain_head(t_token **head, t_token *prev,
					t_token *first_new);
void			ft_attach_tail_and_free(t_token *last, t_token *current);

#endif
