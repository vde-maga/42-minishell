/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:28:35 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:44:50 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: ft_get_target_dir
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Determine the target directory for cd command, handling special cases
 *
 * PARAMETERS
 *   @data: Minishell structure containing environment list
 *   @arg: Directory argument or NULL
 *
 * RETURN VALUE
 *   Pointer to target directory string, or NULL on error
 *
 * NOTES
 *   - Handles "~" and "--" as HOME directory
 *   - Handles "-" as previous directory (OLDPWD) and prints the path
 *   - Returns original arg if no special case matches
 *   - Does not free returned strings - they point to env values or original arg
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: ft_cd_update_env
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Update PWD and OLDPWD environment variables after directory change
 *
 * PARAMETERS
 *   @data: Minishell structure containing environment list
 *   @old_pwd_val: Previous working directory path
 *
 * RETURN VALUE
 *   0 on success, 1 on error
 *
 * NOTES
 *   - Sets OLDPWD to the previous directory if provided
 *   - Gets current directory using getcwd() and sets PWD
 *   - Frees the allocated new_pwd_val before returning
 *   - Memory allocation responsibility: caller must free old_pwd_val
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_cd_update_env(t_minishell *data, char *old_pwd_val)
{
	char	*new_pwd_val;

	if (old_pwd_val)
		ft_set_env_var(&data->env_list, "OLDPWD", old_pwd_val);
	new_pwd_val = getcwd(NULL, 0);
	if (!new_pwd_val)
	{
		perror("minishell: cd: error retrieving current directory");
		return (1);
	}
	ft_set_env_var(&data->env_list, "PWD", new_pwd_val);
	free(new_pwd_val);
	return (0);
}

/*
 * FUNCTION: ft_builtin_cd
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Change the current working directory
 *   and update PWD and OLDPWD environment variables
 *
 * PARAMETERS
 *   @data: Minishell structure containing environment list
 *   @args: Array of arguments where args[1] is the target directory
 *
 * RETURN VALUE
 *   0 on success, 1 on error, 2 if too many arguments
 *
 * NOTES
 *   - Handles special cases: "~", "--" (HOME), "-" (OLDPWD)
 *   - Updates PWD and OLDPWD environment variables
 *     after successful directory change
 *   - Frees allocated memory for old_pwd before returning
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_builtin_cd(t_minishell *data, char **args)
{
	char	*target_dir;
	char	*old_pwd;
	int		status;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
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
