#include "minishell.h"

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
	ft_strlcpy(dest, str + 1, length - 1);
	return (dest);
}

int	ft_expand_quotes(t_token *tokens)
{
	t_token	*current;
	char	*new_value;
	char	*old_value;

	current = tokens;
	while (current)
	{
		if (current->was_quoted == 1)
		{
			new_value = ft_remove_quotes(current->value);
			if (!new_value)
				return (-1);
			old_value = current->value;
			current->value = new_value;
			free(old_value);
		}
		current = current->next;
	}
	return (0);
}