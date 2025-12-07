#include "minishell.h"

int	is_valid_env_var_name(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= 'a' && s[i] <= 'z')
				|| s[i] == '_'
				|| (i > 0 && (s[i] >= '0' && s[i] <= '9'))))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_special_param(char *s)
{
	if (!s || !*s)
		return (0);
	if ((s[0] == '?' || s[0] == '$') && s[1] == '\0')
		return (1);
	return (0);
}

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

// ft_strjoin_char is now implemented as ft_string_append in utils/string_utils.c
char	*ft_strjoin_char(char *s1, char c)
{
	return (ft_string_append(s1, &c, APPEND_CHAR));
}
