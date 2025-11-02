#include "minishell.h"

int	get_shell_pid_from_proc(void)
{
	ssize_t	bytes_read;
	char	buffer[256];
	int		fd;
	int		pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (-1);
	buffer[bytes_read] = '\0';
	pid = ft_atoi(buffer);
	return (pid);
}

char	*ft_get_variable_value(t_env *env, char *var_name)
{
	char	*value;
	t_env	*env_node;

	if (!var_name || !*var_name)
		return (ft_strdup(""));
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(ft_exit_code(-1)));
	else if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(get_shell_pid_from_proc()));
	env_node = ft_get_env_var(env, var_name);
	if (env_node && env_node->value)
		value = ft_strdup(env_node->value);
	else
		value = ft_strdup("");
	return (value);
}

char	*ft_path_tilde_expand(t_env *env, const char *path)
{
	char	*home_dir;
	char	*rest_of_path;
	char	*new_path;

	if (path[0] == '~' && (path[1] == '/' || path[1] == '\0'))
	{
		home_dir = ft_get_variable_value(env, "HOME");
		if (home_dir && *home_dir)
		{
			rest_of_path = (char *)path + 1;
			new_path = ft_strjoin(home_dir, rest_of_path);
			free(home_dir);
			return (new_path);
		}
		if (home_dir)
			free(home_dir);
	}
	return (ft_strdup(path));
}

char	*ft_path_tilde_shorten(t_env *env, const char *path)
{
	char	*home_dir;
	char	*rest_of_path;
	char	*new_path;

	home_dir = ft_get_variable_value(env, "HOME");
	if (home_dir && *home_dir)
	{
		if (ft_strncmp(path, home_dir, ft_strlen(home_dir)) == 0)
		{
			rest_of_path = (char *)path + ft_strlen(home_dir);
			new_path = ft_strjoin("~", rest_of_path);
			free(home_dir);
			return (new_path);
		}
	}
	if (home_dir)
		free(home_dir);
	return (ft_strdup(path));
}
