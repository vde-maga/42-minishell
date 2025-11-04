#include "minishell.h"
#include "expander.h"

static int	ft_new_word_token(const char *word, t_token **out)
{
	t_token	*tmp;

	tmp = ft_calloc(1, sizeof(t_token));
	if (!tmp)
		return (-1);
	tmp->type = TOKEN_WORD;
	tmp->value = ft_strdup(word);
	if (!tmp->value)
	{
		free(tmp);
		return (-1);
	}
	tmp->was_quoted = 0;
	tmp->next = NULL;
	*out = tmp;
	return (0);
}

/* Build a linked list of word tokens from words; returns first and sets last */
t_token	*ft_build_token_chain(char **words, t_token **last_out)
{
	int		i;
	t_token	*first;
	t_token	*last;
	t_token	*tmp;

	i = 0;
	first = NULL;
	last = NULL;
	while (words[i])
	{
		if (ft_new_word_token(words[i], &tmp) < 0)
			return (NULL);
		if (i == 0)
			first = tmp;
		else
			last->next = tmp;
		last = tmp;
		i++;
	}
	if (last_out)
		*last_out = last;
	return (first);
}

/* Link the new chain into the list head/prev position */
void	ft_link_chain_head(t_token **head, t_token *prev, t_token *first_new)
{
	if (prev)
		prev->next = first_new;
	else
		*head = first_new;
}

/* Attach tail to current->next and free current token */
void	ft_attach_tail_and_free(t_token *last, t_token *current)
{
	if (last)
		last->next = current->next;
	free(current->value);
	free(current);
}
