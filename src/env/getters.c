/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:30:30 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:30:31 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_init_minimal_env(void)
{
	t_env	*head;
	char	cwd[PATH_MAX];

	head = NULL;
	if (getcwd(cwd, PATH_MAX) == NULL)
		ft_strlcpy(cwd, "/", PATH_MAX);
	ft_set_env_var(&head, "PWD", cwd);
	ft_set_env_var(&head, "SHLVL", "0");
	ft_set_env_var(&head, "_", "/usr/bin/env");
	ft_set_env_var(&head, "OLDPWD", NULL);
	ft_set_env_var(&head, "PATH",
		"/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.");
	return (head);
}

/*
 * FUNCTION: ft_get_env_list
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Convert external environment array to internal linked list format
 *
 * PARAMETERS
 *   @envp: External environment array (from main function)
 *
 * RETURN VALUE
 *   Pointer to environment list head, or NULL on error
 *
 * NOTES
 *   - Creates minimal environment if envp is NULL/empty
 *   - Converts "VAR=value" strings to internal t_env nodes
 *   - Cleans up on allocation failure
 *   - Memory allocation responsibility: caller owns the list
 * ─────────────────────────────────────────────────────────────────────────
 */
t_env	*ft_get_env_list(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	if (!envp || !*envp)
		return (ft_init_minimal_env());
	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = ft_env_create_node(envp[i]);
		if (!new_node)
		{
			ft_free_env_list(head);
			ft_putstr_fd("Error: failed to create env node\n", 2);
			return (NULL);
		}
		ft_env_add_back(&head, new_node);
		i++;
	}
	return (head);
}

/*
 * FUNCTION: ft_get_env_var
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Search environment list for a variable by name
 *
 * PARAMETERS
 *   @env_list: Head of environment variable list
 *   @var_name: Name of variable to find
 *
 * RETURN VALUE
 *   Pointer to environment node if found, NULL if not found
 *
 * NOTES
 *   - Performs linear search through linked list
 *   - Returns pointer to actual node (not a copy)
 *   - Used by variable expansion and builtin commands
 * ─────────────────────────────────────────────────────────────────────────
 */
t_env	*ft_get_env_var(t_env *env_list, char *var_name)
{
	t_env	*current;

	if (!env_list || !var_name)
		return (NULL);
	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->var, var_name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	ft_env_count_vars(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
