#include "minishell.h"
#include "parser.h"

/*
 * FUNCTION: ft_get_token_before
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Finds the token immediately preceding a target token in a list
 *
 * PARAMETERS
 *   @tokens: Head of token list to search
 *   @target: Token to find the predecessor of
 *
 * RETURN VALUE
 *   Pointer to token before target, or NULL if target is first or not found
 *
 * NOTES
 *   - Used extensively in parser for splitting token lists
 *   - Handles case where target is not in list gracefully
 * ─────────────────────────────────────────────────────────────────────────
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
 * FUNCTION: ft_parser_find_last_operator
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Finds the last occurrence of specified operator types in the token list
 *
 * PARAMETERS
 *   @tokens: Token list to search
 *   @type1: First operator type to match
 *   @type2: Second operator type to match (or -1 to ignore)
 *
 * RETURN VALUE
 *   Pointer to last matching operator token, or NULL if none found
 *
 * NOTES
 *   - Used for implementing operator precedence in parsing
 *   - Returns rightmost operator to ensure left-to-right associativity
 *   - type2 of -1 indicates single type search
 * ─────────────────────────────────────────────────────────────────────────
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
 * FUNCTION: ft_parser_find_last_operator_paren
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Finds the last occurrence of specified operator types outside of parentheses
 *
 * PARAMETERS
 *   @tokens: Token list to search
 *   @type1: First operator type to match
 *   @type2: Second operator type to match (or -1 to ignore)
 *
 * RETURN VALUE
 *   Pointer to last matching operator outside parentheses, or NULL if none found
 *
 * NOTES
 *   - Critical for proper operator precedence handling
 *   - Tracks parenthesis nesting level to ignore operators inside subshells
 *   - Only matches operators at parenthesess level 0 (top level)
 * ─────────────────────────────────────────────────────────────────────────
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
