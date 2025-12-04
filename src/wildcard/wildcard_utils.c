#include "minishell.h"
#include "wildcard.h"

int	ft_should_match_hidden(const char *pattern)
{
	return (pattern[0] == '.');
}

char	*ft_extract_dir_path(const char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup("."));
	if (last_slash == pattern)
		return (ft_strdup("/"));
	return (ft_substr(pattern, 0, last_slash - pattern));
}

char	*ft_extract_basename_pattern(const char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (!last_slash)
		return (ft_strdup(pattern));
	return (ft_strdup(last_slash + 1));
}

char	*ft_build_full_path(const char *dir_path, const char *name)
{
	char	*temp;
	char	*result;

	if (ft_strcmp(dir_path, ".") == 0)
		return (ft_strdup(name));
	temp = ft_strjoin(dir_path, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, name);
	free(temp);
	return (result);
}

void	ft_free_wildcard_ctx(t_wildcard_ctx *ctx)
{
	free(ctx->dir_path);
	free(ctx->basename_pattern);
}
