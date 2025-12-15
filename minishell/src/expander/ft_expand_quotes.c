/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:37 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:47:31 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * FUNCTION: handle_char
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle single character during quote removal process
 *
 * PARAMETERS
 *   @c: Quote context structure containing state
 *
 * RETURN VALUE
 *   None (modifies context structure)
 *
 * NOTES
 *   - Toggles quote mode when encountering quote characters
 *   - Copies non-quote characters to destination
 *   - Single quotes don't affect double quotes and vice versa
 * ─────────────────────────────────────────────────────────────────────────
 */
static void	handle_char(t_qctx *c)
{
	if (c->s[c->i] == '\\' && c->mode == 0 && (c->s[c->i + 1] == '\''
			|| c->s[c->i + 1] == '"'))
	{
		c->d[c->j++] = c->s[c->i + 1];
		c->i += 2;
	}
	else if (c->s[c->i] == '\'' && c->mode != 2)
	{
		if (c->mode == 1)
			c->mode = 0;
		else
			c->mode = 1;
		c->i++;
	}
	else if (c->s[c->i] == '"' && c->mode != 1)
	{
		if (c->mode == 2)
			c->mode = 0;
		else
			c->mode = 2;
		c->i++;
	}
	else
		c->d[c->j++] = c->s[c->i++];
}

/*
 * FUNCTION: fill_without_quotes
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Copy string to destination while removing quote characters
 *
 * PARAMETERS
 *   @str: Source string with quotes
 *   @dest: Destination buffer
 *   @mode: Final quote mode (output parameter)
 *
 * RETURN VALUE
 *   Length of destination string
 *
 * NOTES
 *   - Handles nested quotes and quote state tracking
 *   - Mode: 0 = no quotes, 1 = single quotes, 2 = double quotes
 *   - Used internally by ft_remove_quotes
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	fill_without_quotes(const char *str, char *dest, int *mode)
{
	t_qctx			c;

	c.s = str;
	c.d = dest;
	c.i = 0;
	c.j = 0;
	c.mode = 0;
	while (c.s[c.i])
		handle_char(&c);
	dest[c.j] = '\0';
	*mode = c.mode;
	return (c.j);
}

/*
 * FUNCTION: ft_remove_quotes
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Remove quotes from string while preserving escaped content
 *
 * PARAMETERS
 *   @str: Input string potentially containing quotes
 *
 * RETURN VALUE
 *   New string without quotes, or NULL on allocation failure
 *
 * NOTES
 *   - Handles both single and double quotes
 *   - Preserves quote content (except quote characters themselves)
 *   - Returns original string duplicated if no quotes found
 *   - Memory allocation responsibility: caller must free returned string
 * ─────────────────────────────────────────────────────────────────────────
 */
char	*ft_remove_quotes(char *str)
{
	char			*dest;
	int				mode;
	int				j;

	if (!str)
		return (NULL);
	dest = (char *)malloc(ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	j = fill_without_quotes(str, dest, &mode);
	if (mode != 0 || j == (int)ft_strlen(str))
	{
		free(dest);
		return (ft_strdup(str));
	}
	return (dest);
}

/*
 * FUNCTION: ft_exp_replace_content
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Replace token value with environment variable content
 *
 * PARAMETERS
 *   @env: Environment list for variable lookup
 *   @current: Token to modify
 *   @var_name: Name of variable to look up
 *
 * RETURN VALUE
 *   0 on success, -1 on memory allocation failure
 *
 * NOTES
 *   - Replaces token value with variable value or empty string if not found
 *   - Frees old token value before replacement
 *   - Memory allocation responsibility: function manages token value memory
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exp_replace_content(t_env *env, t_token *current, char *var_name)
{
	char		*new_value;
	char		*old_value;
	t_env		*env_node;

	env_node = ft_get_env_var(env, var_name);
	if (env_node && env_node->value)
		new_value = ft_strdup(env_node->value);
	else
		new_value = ft_strdup("");
	if (!new_value)
		return (-1);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}

/*
 * FUNCTION: ft_exp_special_param
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Handle special shell parameters ($$, $?, etc.)
 *
 * PARAMETERS
 *   @msdata: Minishell structure (unused)
 *   @current: Token to modify
 *   @var_name: Variable name (unused)
 *
 * RETURN VALUE
 *   0 on success
 *
 * NOTES
 *   - $$ expands to shell PID
 *   - $? expands to last exit code
 *   - Falls back to 42 for unknown special parameters
 *   - Memory allocation responsibility: function manages token value memory
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_exp_special_param(t_minishell *msdata, t_token *current, char *var_name)
{
	char		*new_value;
	char		*old_value;

	(void)var_name;
	(void)msdata;
	if (ft_strcmp(current->value, "$$") == 0)
		new_value = ft_itoa(get_shell_pid_from_proc());
	else if (ft_strcmp(current->value, "$?") == 0)
		new_value = ft_itoa(ft_exit_code(-1));
	else
		new_value = ft_itoa(42);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}
