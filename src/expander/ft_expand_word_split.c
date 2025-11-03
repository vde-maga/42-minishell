#include "minishell.h"

static t_token	*ft_create_word_token(char *word)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = TOKEN_WORD;
	new_token->value = ft_strdup(word);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->was_quoted = 0;
	new_token->next = NULL;
	return (new_token);
}

static void	ft_free_word_array(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static t_token	*ft_replace_token_with_split(t_token **head,
		t_token *prev, t_token *current, char **words)
{
	t_token	*first_new;
	t_token	*temp;
	t_token	*last;
	int		i;

	i = 0;
	first_new = NULL;
	last = NULL;
	while (words[i])
	{
		temp = ft_create_word_token(words[i]);
		if (!temp)
			return (NULL);
		if (i == 0)
		{
			first_new = temp;
			if (prev)
				prev->next = first_new;
			else
				*head = first_new;
		}
		else
			last->next = temp;
		last = temp;
		i++;
	}
	if (last)
		last->next = current->next;
	free(current->value);
	free(current);
	return (last);
}

int	ft_apply_word_splitting(t_token **head, t_token *prev,
		t_token *current, char **words)
{
	t_token	*last;

	if (!words || !words[0])
	{
		if (prev)
			prev->next = current->next;
		else
			*head = current->next;
		free(current->value);
		free(current);
		return (1);
	}
	last = ft_replace_token_with_split(head, prev, current, words);
	if (!last)
		return (-1);
	ft_free_word_array(words);
	return (1);
}
