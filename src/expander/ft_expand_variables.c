#include "minishell.h"
#include "structs.h"
#include "lexer.h"

static int	ft_should_apply_word_split(t_token *current, int var_expanded)
{
	int	i;

	if (!var_expanded)
		return (0);
	if (current->was_quoted)
		return (0);
	if (!current->value)
		return (1);
	if (current->value[0] == '\0')
		return (1);
	i = 0;
	while (current->value[i])
	{
		if (current->value[i] == ' ' || current->value[i] == '\t'
			|| current->value[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_expand_and_split_token(t_minishell *msdata, t_env *env,
			t_token **prev_ptr, t_token **curr_ptr)
{
	t_token	*current;
	t_token	*prev;
	char	**words;
	int		var_expanded;

	current = *curr_ptr;
	prev = *prev_ptr;
	var_expanded = ft_process_token_expansion(msdata, env, current);
	if (var_expanded < 0)
		return (-1);
	if (ft_should_apply_word_split(current, var_expanded))
	{
		words = ft_word_split(current->value);
		if (ft_apply_word_splitting(&msdata->tokens, prev, current, words) < 0)
			return (-1);
		if (prev)
			*curr_ptr = prev->next;
		else
			*curr_ptr = msdata->tokens;
		return (1);
	}
	*prev_ptr = current;
	*curr_ptr = current->next;
	return (0);
}

int	ft_expand_variables(t_minishell *msdata, t_env *env)
{
	t_token	*current;
	t_token	*prev;
	int		result;

	if (!msdata || !env)
		return (-1);
	current = msdata->tokens;
	prev = NULL;
	while (current)
	{
		result = ft_expand_and_split_token(msdata, env, &prev, &current);
		if (result < 0)
			return (-1);
	}
	return (0);
}
