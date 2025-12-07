#include "minishell.h"

/*
 * FUNCTION: ft_is_flagged
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Check if argument is a valid echo -n flag
 *
 * PARAMETERS
 *   @arg: Argument string to validate
 *
 * RETURN VALUE
 *   1 if valid -n flag, 0 if not
 *
 * NOTES
 *   - Must start with "-n" and contain only 'n' characters after
 *   - Accepts "-n", "-nn", "-nnn", etc.
 *   - Returns 0 for "-" or any string with non-'n' characters
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	ft_is_flagged(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
 * FUNCTION: ft_builtin_echo
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Display arguments to standard output with optional newline suppression
 *
 * PARAMETERS
 *   @args: Array of arguments where args[1+] are strings to echo
 *
 * RETURN VALUE
 *   Always returns 0 (success)
 *
 * NOTES
 *   - Supports -n flag to suppress trailing newline
 *   - Multiple -n flags are processed (any sequence of 'n' after '-')
 *   - Arguments are separated by single spaces
 *   - No arguments prints just a newline (unless -n flag used)
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_builtin_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (args[i] && ft_is_flagged(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
