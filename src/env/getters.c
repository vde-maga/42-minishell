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
	ft_set_env_var(&head, "PATH", "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:.");
	return (head);
}

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
