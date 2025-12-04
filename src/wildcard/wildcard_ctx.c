#include "minishell.h"
#include "wildcard.h"

int	ft_init_ctx(t_wildcard_ctx *ctx, const char *pattern)
{
	ctx->dir_path = ft_extract_dir_path(pattern);
	ctx->basename_pattern = ft_extract_basename_pattern(pattern);
	if (!ctx->dir_path || !ctx->basename_pattern)
	{
		ft_free_wildcard_ctx(ctx);
		return (0);
	}
	ctx->should_match_hidden = ft_should_match_hidden(ctx->basename_pattern);
	return (1);
}
