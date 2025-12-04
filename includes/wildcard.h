#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include "structs.h"
# include "lexer.h"

/*
** Function to check if a token contains unquoted wildcards
*/
int		ft_has_unquoted_wildcards(const char *str);

/*
** Pattern matching function for wildcards
*/
int		ft_wildcard_match(const char *pattern, const char *str);

/*
** Function to expand wildcards in a token
*/
int		ft_expand_wildcards(t_token **head, t_token *prev, t_token *current);

/*
** Helper function to get directory entries matching a pattern
*/
char	**ft_get_matching_files(const char *pattern);

/*
** Function to check if pattern should match hidden files
*/
int		ft_should_match_hidden(const char *pattern);

/*
** Function to extract directory path from pattern
*/
char	*ft_extract_dir_path(const char *pattern);

/*
** Function to extract basename pattern from full path
*/
char	*ft_extract_basename_pattern(const char *pattern);

#endif