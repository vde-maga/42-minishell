#include "minishell.h"
#include "expander.h"

void	append_char_free(char **res, char c)
{
	char	*tmp;

	tmp = ft_strjoin_char(*res, c);
	// ft_strjoin_char now calls ft_string_append which already frees the original
	// so we don't need to free(*res) here
	*res = tmp;
}

/* process_escape is defined in ft_expand_utils.c */

int	collect_or_special(const char *s, int j, char *name)
{
	int	k;

	k = 0;
	if (s[j] == '?' || s[j] == '$')
	{
		name[0] = s[j];
		name[1] = '\0';
		return (j + 1);
	}
	while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
	{
		if (k < 255)
		{
			name[k] = s[j];
			k++;
		}
		j++;
	}
	name[k] = '\0';
	return (j);
}

static int	handle_dollar_quoted(t_expand_ctx *ctx, int i, int j)
{
	char	q;

	q = ctx->s[j];
	j = i + 2;
	while (ctx->s[j] && ctx->s[j] != q)
		append_char_free(ctx->res, ctx->s[j++]);
	if (ctx->s[j] == q)
		j++;
	return (j);
}

int	handle_dollar_ctx(t_expand_ctx *ctx, int i)
{
	int		j;
	char	name[256];
	char	*val;
	char	*tmp;

	j = i + 1;
	if (((ctx->s[j] == '"') || (ctx->s[j] == '\'')) && !ctx->in_d)
		return (handle_dollar_quoted(ctx, i, j));
	j = collect_or_special(ctx->s, j, name);
	if (name[0] != '\0')
	{
		val = ft_get_variable_value(ctx->env, name);
		if (val)
		{
			if (!ctx->in_d && ctx->unquoted_expand)
				*ctx->unquoted_expand = 1;
			tmp = ft_strjoin(*ctx->res, val);
			free(*ctx->res);
			*ctx->res = tmp;
			free(val);
		}
		return (j);
	}
	append_char_free(ctx->res, ctx->s[i]);
	return (i + 1);
}

void	expander_step(t_expand_ctx *ctx, int *i, int *in_s, int *in_d)
{
	if (ctx->s[*i] == '\'' && !*in_d)
	{
		*in_s = !*in_s;
		append_char_free(ctx->res, ctx->s[(*i)++]);
		return ;
	}
	if (ctx->s[*i] == '"' && !*in_s)
	{
		*in_d = !*in_d;
		append_char_free(ctx->res, ctx->s[(*i)++]);
		return ;
	}
	if (ctx->s[*i] == '\\' && !*in_s)
		return (process_escape(ctx->s, i, ctx->res));
	if (ctx->s[*i] == '$' && !*in_s)
	{
		ctx->in_d = *in_d;
		*i = handle_dollar_ctx(ctx, *i);
		return ;
	}
	append_char_free(ctx->res, ctx->s[(*i)++]);
}
