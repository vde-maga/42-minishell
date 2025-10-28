#include "minishell.h"

static char	*ft_get_target_dir(t_minishell *data, char *path)
{
	t_env	*home;
	t_env	*old_pwd;

	if (!path || path[0] == '\0' || ft_strcmp(path, "~") == 0)
	{
		home = ft_get_env_var(data->env_list, "HOME");
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (home->value);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		old_pwd = ft_get_env_var(data->env_list, "OLDPWD");
		if (!old_pwd)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		return (old_pwd->value);
	}
	return (path);
}

static int	ft_update_pwd_vars(t_minishell *data, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	ft_update_env_var(data->env_list, "OLDPWD", old_pwd);
	ft_update_env_var(data->env_list, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_builtin_cd(t_minishell *data, char *path)
{
	char	*target_dir;
	char	*old_pwd;

	target_dir = ft_get_target_dir(data, path);
	if (!target_dir)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		free(old_pwd);
		return (1);
	}
	ft_update_pwd_vars(data, old_pwd);
	free(old_pwd);
	return (0);
}
