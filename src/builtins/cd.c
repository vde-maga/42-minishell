#include "minishell.h"

static char	*ft_get_target_dir(t_minishell *data, char *arg)
{
	t_env	*env;

	if (!arg || ft_strcmp(arg, "~") == 0 || ft_strcmp(arg, "--") == 0)
	{
		env = ft_get_env_var(data->env_list, "HOME");
		if (!env || !env->value || env->value[0] == '\0')
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (env->value);
	}
	if (ft_strcmp(arg, "-") == 0)
	{
		env = ft_get_env_var(data->env_list, "OLDPWD");
		if (!env || !env->value)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		ft_putendl_fd(env->value, 1);
		return (env->value);
	}
	return (arg);
}

static int	ft_cd_update_env(t_minishell *data, char *old_pwd_val)
{
	char	*new_pwd_val;

	if (old_pwd_val)
		ft_update_env_var(data->env_list, "OLDPWD", old_pwd_val);
	new_pwd_val = getcwd(NULL, 0);
	if (!new_pwd_val)
	{
		perror("minishell: cd: error retrieving current directory");
		return (1);
	}
	ft_update_env_var(data->env_list, "PWD", new_pwd_val);
	free(new_pwd_val);
	return (0);
}

int	ft_builtin_cd(t_minishell *data, char **args)
{
	char	*target_dir;
	char	*old_pwd;
	int		status;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 2);
	target_dir = ft_get_target_dir(data, args[1]);
	if (!target_dir)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (free(old_pwd), 1);
	}
	status = ft_cd_update_env(data, old_pwd);
	free(old_pwd);
	return (status);
}
