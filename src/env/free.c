#include "minishell.h"

/*
 * FUNCTION: ft_free_env_list
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free an entire environment variable list
 *
 * PARAMETERS
 *   @head: Head of environment list to free
 *
 * RETURN VALUE
 *   None
 *
 * NOTES
 *   - Frees variable name, value, and node structure
 *   - Handles NULL input gracefully
 *   - Used during shell cleanup and error handling
 *   - Memory allocation responsibility: function manages entire list cleanup
 * ─────────────────────────────────────────────────────────────────────────
 */
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
