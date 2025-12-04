/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard.h"

typedef struct s_wildcard_ctx
{
	char	*dir_path;
	char	*basename_pattern;
	int		should_match_hidden;
}	t_wildcard_ctx;

static int	ft_skip_entry(struct dirent *entry, t_wildcard_ctx *ctx)
{
	int	is_dot;
	int	is_dotdot;
	int	pattern_is_dot;
	int	pattern_is_dotdot;

	is_dot = (ft_strcmp(entry->d_name, ".") == 0);
	is_dotdot = (ft_strcmp(entry->d_name, "..") == 0);
	pattern_is_dot = (ft_strcmp(ctx->basename_pattern, ".") == 0);
	pattern_is_dotdot = (ft_strcmp(ctx->basename_pattern, "..") == 0);
	if ((is_dot || is_dotdot) && !pattern_is_dot && !pattern_is_dotdot)
		return (1);
	if (entry->d_name[0] == '.' && !ctx->should_match_hidden)
		return (1);
	return (0);
}

static int	ft_count_matches(DIR *dir, t_wildcard_ctx *ctx)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!ft_skip_entry(entry, ctx))
		{
			if (ft_wildcard_match(ctx->basename_pattern, entry->d_name))
				count++;
		}
		entry = readdir(dir);
	}
	return (count);
}

static char	*ft_build_full_path(const char *dir_path, const char *name)
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

static char	**ft_collect_matches(DIR *dir, t_wildcard_ctx *ctx, int count)
{
	struct dirent	*entry;
	char			**matches;
	int				i;

	matches = ft_calloc(count + 1, sizeof(char *));
	if (!matches)
		return (NULL);
	rewinddir(dir);
	i = 0;
	entry = readdir(dir);
	while (entry != NULL && i < count)
	{
		if (!ft_skip_entry(entry, ctx))
		{
			if (ft_wildcard_match(ctx->basename_pattern, entry->d_name))
			{
				matches[i] = ft_build_full_path(ctx->dir_path, entry->d_name);
				i++;
			}
		}
		entry = readdir(dir);
	}
	return (matches);
}

static void	ft_free_wildcard_ctx(t_wildcard_ctx *ctx)
{
	free(ctx->dir_path);
	free(ctx->basename_pattern);
}

static int	ft_init_ctx(t_wildcard_ctx *ctx, const char *pattern)
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

char	**ft_get_matching_files(const char *pattern)
{
	t_wildcard_ctx	ctx;
	DIR				*dir;
	int				count;
	char			**matches;

	if (!ft_init_ctx(&ctx, pattern))
		return (NULL);
	dir = opendir(ctx.dir_path);
	if (!dir)
	{
		ft_free_wildcard_ctx(&ctx);
		return (NULL);
	}
	count = ft_count_matches(dir, &ctx);
	if (count == 0)
	{
		closedir(dir);
		ft_free_wildcard_ctx(&ctx);
		return (NULL);
	}
	matches = ft_collect_matches(dir, &ctx, count);
	closedir(dir);
	ft_free_wildcard_ctx(&ctx);
	return (matches);
}
