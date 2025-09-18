#include "../../includes/minishell.h"

char	*ft_remove_quotes(char *str)
{
	char	*dest;
	int		length;

	if (!str)
		return (NULL);
	length = ft_strlen(str);
	if (length < 2)
	{
		dest = ft_strdup(str);
		if (!dest)
			return (NULL);
		return (dest);
	}
	dest = (char *)malloc(sizeof(char) * (length - 2 + 1));
	if (!dest)
		return (NULL);
//	ft_strlcpy(dest, str + 1, length - 1);
	ft_strlcpy(dest, str + 1, length - 1);
	return (dest);
}


t_token *ft_expander(t_token *tokens, t_env *env)
{
	t_token	*current_token;
	t_token *first;
	char	*new_value;
	char	*old_value;

	(void)env;
//	first = tokens;
	current_token = tokens;
	first = current_token;
	while (current_token)
	{
		if (current_token->was_quoted == 1)
		{
			new_value = ft_remove_quotes(current_token->value);
			if (!new_value)
//				 return ;
				 return (NULL);
			old_value = current_token->value;
			current_token->value = new_value;
			free(old_value);
		}
		current_token = current_token->next;
	}
	return (first);
}
