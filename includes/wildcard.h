/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:22 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:44:23 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>

typedef struct s_wildcard_ctx
{
	char	*dir_path;
	char	*basename_pattern;
	int		should_match_hidden;
}	t_wildcard_ctx;

/* wildcard.c */
int		ft_expand_wildcards(t_token **head, t_token *prev, t_token *current);

/* wildcard_dir.c */
char	**ft_get_matching_files(const char *pattern);

/* wildcard_match.c */
int		ft_has_unquoted_wildcards(const char *str);
int		ft_wildcard_match(const char *pattern, const char *str);

/* wildcard_utils.c */
int		ft_should_match_hidden(const char *pattern);
char	*ft_extract_dir_path(const char *pattern);
char	*ft_extract_basename_pattern(const char *pattern);

/* wildcard_ctx.c */
int		ft_init_ctx(t_wildcard_ctx *ctx, const char *pattern);
void	ft_free_wildcard_ctx(t_wildcard_ctx *ctx);
char	*ft_build_full_path(const char *dir_path, const char *name);

#endif
