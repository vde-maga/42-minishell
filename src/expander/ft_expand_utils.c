#include "minishell.h"

static int	init_expand(t_expand_ctx *ctx, char **res, t_env *env, char *s)
{
	*res = ft_strdup("");
	if (!*res)
		return (0);
	ctx->env = env;
	ctx->s = s;
	ctx->res = res;
	return (1);
}

static void	init_state(int *i, int *in_s, int *in_d)
{
	*i = 0;
	*in_s = 0;
	*in_d = 0;
}

char	*ft_expand_variables_in_string(t_env *env, char *s,
	int *unquoted_expand)
{
	t_expand_ctx	ctx;
	char			*res;
	int				i;
	int				in_s;
	int				in_d;

	if (!s)
		return (NULL);
	if (!init_expand(&ctx, &res, env, s))
		return (NULL);
	ctx.unquoted_expand = unquoted_expand;
	if (unquoted_expand)
		*unquoted_expand = 0;
	init_state(&i, &in_s, &in_d);
	while (s[i])
	{
		ctx.in_d = in_d;
		expander_step(&ctx, &i, &in_s, &in_d);
	}
	return (res);
}

char	*ft_strjoin_char(char *s1, char c)
{
	return (ft_string_append(s1, &c, APPEND_CHAR));
}
