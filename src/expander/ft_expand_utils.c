#include "minishell.h"
#include "expander.h"

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

/* helpers moved to ft_expand_helpers.c */

void	process_escape(const char *s, int *i, char **res)
{
	(*i)++;
	if (s[*i])
		append_char_free(res, s[(*i)++]);
	else
		append_char_free(res, '\\');
}

char	*ft_expand_variables_in_string(t_env *env, char *s)
{
	t_expand_ctx	ctx;
	char			*res;
	int				i;
	int				in_s;
	int				in_d;

	if (!s)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	ctx.env = env;
	ctx.s = s;
	ctx.res = &res;
	i = 0;
	in_s = 0;
	in_d = 0;
	while (s[i])
	{
		ctx.in_d = in_d;
		expander_step(&ctx, &i, &in_s, &in_d);
	}
	return (res);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*res;
	int		len;

	if (!s1)
	{
		res = malloc(2);
		if (res)
		{
			res[0] = c;
			res[1] = '\0';
		}
		return (res);
	}
	len = ft_strlen(s1);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
}
