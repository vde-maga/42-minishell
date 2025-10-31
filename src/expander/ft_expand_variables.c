#include "minishell.h"
#include "structs.h"
#include "lexer.h"

// TODO: Implement word splitting functions for future use
// Word splitting requires rebuilding the entire token list to avoid iterator invalidation

int	ft_expand_variables(t_minishell *msdata, t_env *env)
{
	t_token	*current;
	int		ret_val;
	char	*old_value;
	char	*expanded_value;

	if (!msdata || !env)
		return (-1);

	current = msdata->tokens;
	ret_val = 0;
	while (current)
	{
		if (current->value && current->type == TOKEN_WORD)
		{
			// Check if this is a quoted heredoc delimiter
			// A token is a heredoc delimiter if it follows a << operator
			int is_heredoc_delim = 0;
			t_token *temp = msdata->tokens;
			while (temp && temp->next)
			{
				if (temp->type == TOKEN_HEREDOC && temp->next == current)
				{
					is_heredoc_delim = 1;
					break;
				}
				temp = temp->next;
			}

			if (ft_strchr(current->value, '$'))
			{
				// Skip variable expansion for quoted heredoc delimiters
				if (!is_heredoc_delim || !current->was_quoted)
				{
					// Variable expansion - word splitting to be implemented later

					expanded_value = ft_expand_variables_in_string(env, current->value);
					if (expanded_value)
					{
						old_value = current->value;
						current->value = expanded_value;
						free(old_value);
					}
					else
					{
						// Expansion failed, return error
						return (-1);
					}

					// TODO: Implement word splitting for unquoted variables
					// This requires rebuilding the token list to avoid iterator invalidation
					// For now, we'll keep the current behavior
				}
			}
			// Remove quotes after variable expansion
			char *unquoted_value = ft_remove_quotes(current->value);
			if (unquoted_value)
			{
				old_value = current->value;
				current->value = unquoted_value;
				free(old_value);
			}
			else
			{
				// Quote removal failed, return error
				return (-1);
			}
		}
		current = current->next;
	}
	return (ret_val);
}
