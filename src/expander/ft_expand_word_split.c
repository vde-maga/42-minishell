#include "minishell.h"

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
	t_token	*last;

	first_new = NULL;
	last = NULL;
	first_new = ft_build_token_chain(words, &last);
	if (!first_new || !last)
		return (NULL);
	ft_link_chain_head(head, prev, first_new);
	ft_attach_tail_and_free(last, current);
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
