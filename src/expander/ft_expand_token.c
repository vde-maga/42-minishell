#include "minishell.h"

static int	ft_is_heredoc_delim(t_minishell *msdata, t_token *current)
{
	t_token	*temp;

	temp = msdata->tokens;
	while (temp && temp->next)
	{
		if (temp->type == TOKEN_HEREDOC && temp->next == current)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	ft_expand_var_in_token(t_env *env, t_token *current,
				int is_heredoc_delim)
{
	char	*expanded_value;
	char	*old_value;

	if (!ft_strchr(current->value, '$'))
		return (0);
	if (is_heredoc_delim && current->was_quoted)
		return (0);
	expanded_value = ft_expand_variables_in_string(env, current->value);
	if (!expanded_value)
		return (-1);
	old_value = current->value;
	current->value = expanded_value;
	free(old_value);
	return (1);
}

static int	ft_remove_quotes_from_token(t_token *current)
{
	char	*unquoted_value;
	char	*old_value;

	unquoted_value = ft_remove_quotes(current->value);
	if (!unquoted_value)
		return (-1);
	old_value = current->value;
	current->value = unquoted_value;
	free(old_value);
	return (0);
}

static int	ft_expand_tilde_in_token(t_env *env, t_token *current)
{
	char	*expanded_path;

	if (current->value[0] != '~' || current->was_quoted)
		return (0);
	expanded_path = ft_path_tilde_expand(env, current->value);
	if (!expanded_path)
		return (0);
	free(current->value);
	current->value = expanded_path;
	return (0);
}

int	ft_process_token_expansion(t_minishell *msdata, t_env *env,
		t_token *current)
{
	int	is_heredoc_delim;
	int	var_expanded;

	if (!current->value || current->type != TOKEN_WORD)
		return (0);
	ft_expand_tilde_in_token(env, current);
	is_heredoc_delim = ft_is_heredoc_delim(msdata, current);
	var_expanded = ft_expand_var_in_token(env, current, is_heredoc_delim);
	if (var_expanded < 0)
		return (-1);
	if (ft_remove_quotes_from_token(current) < 0)
		return (-1);
	return (var_expanded);
}
