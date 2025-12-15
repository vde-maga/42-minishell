/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:01 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:46:51 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_path_dirs(t_env *env)
{
	t_env	*cur_env;

	cur_env = env;
	while (cur_env)
	{
		if (ft_strcmp(cur_env->var, "PATH") == 0)
			return (ft_split(cur_env->value, ':'));
		cur_env = cur_env->next;
	}
	return (NULL);
}

static char	*ft_find_cmd_in_path(char *cmd, char **paths)
{
	char		*full_path;
	char		*temp_path;
	int			i;
	struct stat	st;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (stat(full_path, &st) == 0 && !S_ISDIR(st.st_mode)
			&& access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*ft_check_current_dir(char *cmd)
{
	char		*full_path;
	char		*cwd;
	struct stat	st;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	full_path = ft_strjoin(cwd, "/");
	free(cwd);
	if (!full_path)
		return (NULL);
	cwd = ft_strjoin(full_path, cmd);
	free(full_path);
	if (!cwd)
		return (NULL);
	if (stat(cwd, &st) == 0 && !S_ISDIR(st.st_mode)
		&& access(cwd, X_OK) == 0)
		return (cwd);
	free(cwd);
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, t_env *env_list)
{
	char			*path;
	char			**path_dirs;
	struct stat		st;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		{
			errno = EISDIR;
			return (NULL);
		}
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_dirs = ft_get_path_dirs(env_list);
	if (!path_dirs)
		return (ft_check_current_dir(cmd));
	path = ft_find_cmd_in_path(cmd, path_dirs);
	ft_free_str_arrays(path_dirs);
	return (path);
}
