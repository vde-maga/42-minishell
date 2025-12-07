#include "minishell.h"
#include "wildcard.h"

static int	ft_count_matches(char **matches)
{
	int	count;

	count = 0;
	while (matches[count])
		count++;
	return (count);
}

static void	ft_sort_matches(char **matches, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(matches[j], matches[j + 1]) > 0)
			{
				temp = matches[j];
				matches[j] = matches[j + 1];
				matches[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static t_token	*ft_create_new_token(char *value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = TOKEN_WORD;
	new_token->was_quoted = 0;
	new_token->next = NULL;
	return (new_token);
}

static int	ft_insert_tokens(t_token *current, char **matches, int count)
{
	t_token	*new_token;
	t_token	*last;
	int		i;

	free(current->value);
	current->value = matches[0];
	last = current;
	i = 1;
	while (i < count)
	{
		new_token = ft_create_new_token(matches[i]);
		if (!new_token)
			return (0);
		new_token->next = last->next;
		last->next = new_token;
		last = new_token;
		i++;
	}
	return (1);
}

int	ft_expand_wildcards(t_token **head, t_token *prev, t_token *current)
{
	char	**matches;
	int		count;
	int		result;

	(void)head;
	(void)prev;
	if (!current || !current->value || current->type != TOKEN_WORD)
		return (0);
	if (current->was_quoted || !ft_has_unquoted_wildcards(current->value))
		return (0);
	matches = ft_get_matching_files(current->value);
	if (!matches)
		return (0);
	count = ft_count_matches(matches);
	ft_sort_matches(matches, count);
	result = ft_insert_tokens(current, matches, count);
	free(matches);
	return (result);
}
