#include "minishell.h"

void	ft_free_env_list(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head->next;
		free(head->var);
		free(head->value);
		free(head);
		head = temp;
	}
}

static int	ft_fill_env_node(t_env *node, char *envp_line, char *split_pos)
{
	int	var_len;

	var_len = split_pos - envp_line;
	node->var = malloc(sizeof(char) * (var_len + 1));
	if (!node->var)
		return (1);
	ft_strlcpy(node->var, envp_line, var_len + 1);
	node->value = ft_strdup(split_pos + 1);
	if (!node->value)
	{
		free(node->var);
		return (1);
	}
	return (0);
}

t_env	*ft_env_create_node(char *envp_line)
{
	t_env	*new_node;
	char	*equal_sign_pos;
	int		fill_status;

	equal_sign_pos = ft_strchr(envp_line, '=');
	if (!equal_sign_pos)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	fill_status = ft_fill_env_node(new_node, envp_line, equal_sign_pos);
	if (fill_status == 1)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_env_add_back(t_env **lst, t_env *new_node)
{
	t_env	*last;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

t_env	*ft_get_env_list(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	int		i;

	if (!envp || !*envp)
		return (NULL);
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
