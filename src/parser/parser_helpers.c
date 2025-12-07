#include "minishell.h"
#include "parser.h"

/*
 * Finds the token immediately preceding a target token in a list.
 */
t_token	*ft_get_token_before(t_token *tokens, t_token *target)
{
	t_token	*current;

	current = tokens;
	while (current && current->next != target)
		current = current->next;
	return (current);
}

/*
 * Finds the last occurrence of specified operator types in the token list.
 */
t_token	*ft_parser_find_last_operator(t_token *tokens, t_token_type type1,
		t_token_type type2)
{
	t_token	*last_operator;
	t_token	*current;

	last_operator = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == type1 || (type2 != (t_token_type) - 1
				&& current->type == type2))
			last_operator = current;
		current = current->next;
	}
	return (last_operator);
}

/*
 * Finds the last occurrence of specified operator types outside of parentheses.
 */
t_token	*ft_parser_find_last_operator_paren(t_token *tokens, t_token_type type1,
		t_token_type type2)
{
	t_token	*last_operator;
	t_token	*current;
	int		paren_count;

	last_operator = NULL;
	current = tokens;
	paren_count = 0;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			paren_count++;
		else if (current->type == TOKEN_RPAREN)
			paren_count--;
		else if (paren_count == 0 && (current->type == type1
				|| (type2 != (t_token_type) - 1 && current->type == type2)))
			last_operator = current;
		current = current->next;
	}
	return (last_operator);
}
