#include "minishell.h"

void	process_escape(const char *s, int *i, char **res)
{
	(*i)++;
	if (s[*i])
		append_char_free(res, s[(*i)++]);
	else
		append_char_free(res, '\\');
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
