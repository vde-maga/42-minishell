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
	char	*full_path;
	char	*temp_path;
	int		i;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
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
	path = ft_find_cmd_in_path(cmd, path_dirs);
	ft_free_str_arrays(path_dirs);
	return (path);
}
