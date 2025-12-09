/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:35:04 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:49:17 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "wildcard.h"

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

static int	ft_count_dir_matches(DIR *dir, t_wildcard_ctx *ctx)
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

static char	**ft_collect_matches(DIR *dir, t_wildcard_ctx *ctx, int count)
{
	struct dirent	*entry;
	char			**matches;
	int				i;

	matches = ft_calloc(count + 1, sizeof(char *));
	if (!matches)
		return (NULL);
	i = 0;
	entry = readdir(dir);
	while (entry != NULL && i < count)
	{
		if (!ft_skip_entry(entry, ctx))
		{
			if (ft_wildcard_match(ctx->basename_pattern, entry->d_name))
				matches[i++] = ft_build_full_path(ctx->dir_path, entry->d_name);
		}
		entry = readdir(dir);
	}
	return (matches);
}

static char	**ft_process_matches(DIR **dir, t_wildcard_ctx *ctx)
{
	int	count;

	count = ft_count_dir_matches(*dir, ctx);
	if (count == 0)
		return (NULL);
	closedir(*dir);
	*dir = opendir(ctx->dir_path);
	if (!*dir)
		return (NULL);
	return (ft_collect_matches(*dir, ctx, count));
}

/*
 * FUNCTION: ft_get_matching_files
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Expands wildcard pattern and returns array of matching file names
 *
 * PARAMETERS
 *   pattern: Wildcard pattern to match against directory contents
 *
 * RETURN VALUE
 *   NULL-terminated array of matching file names, NULL on error
 *
 * NOTES
 *   - Handles patterns like *, ?, and character classes
 *   - Skips hidden files unless explicitly matched
 *   - Returns full paths for matched files
 *   - Caller is responsible for freeing the array and strings
 * ─────────────────────────────────────────────────────────────────────────
 */
char	**ft_get_matching_files(const char *pattern)
{
	t_wildcard_ctx	ctx;
	DIR				*dir;
	char			**matches;

	if (!ft_init_ctx(&ctx, pattern))
		return (NULL);
	dir = opendir(ctx.dir_path);
	if (!dir)
	{
		ft_free_wildcard_ctx(&ctx);
		return (NULL);
	}
	matches = ft_process_matches(&dir, &ctx);
	if (dir)
		closedir(dir);
	ft_free_wildcard_ctx(&ctx);
	return (matches);
}
