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
