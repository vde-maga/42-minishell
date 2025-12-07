#include "minishell.h"
#include "exit_utils.h"
#include "exit_handlers.h"

/*
 * FUNCTION: ft_is_numeric
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Check if a string represents a valid numeric value
 *
 * PARAMETERS
 *   @str: String to validate
 *
 * RETURN VALUE
 *   1 if string is numeric, 0 if not
 *
 * NOTES
 *   - Allows optional leading '+' or '-' sign
 *   - Requires at least one digit after optional sign
 *   - Empty strings or sign-only strings are invalid
 *   - Used for validating exit command arguments
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * FUNCTION: ft_exit_free_and_exit
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Free all allocated memory and exit the shell
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing shell state
 *   @exit_code: Exit code to pass to exit()
 *
 * RETURN VALUE
 *   Does not return (calls exit())
 *
 * NOTES
 *   - Frees tokens, parser, and shell data structures
 *   - Handles NULL pointers gracefully
 *   - This is the final cleanup before process termination
 *   - Memory allocation responsibility: function frees all shell memory
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_exit_free_and_exit(t_minishell *msdata, int exit_code)
{
	if (msdata && msdata->tokens)
		ft_tokens_free(msdata->tokens);
	if (msdata && msdata->parser)
		ft_parser_free(msdata->parser);
	if (msdata)
		ft_free_shell(msdata, 0);
	exit(exit_code);
}

static int	ft_is_llong(const char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		if (res > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (str[i] == '\0');
}

/*
 * FUNCTION: ft_builtin_exit
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Exit the shell with an optional exit code
 *
 * PARAMETERS
 *   @msdata: Minishell structure containing shell state
 *   @args: Array of arguments where args[0] is the exit code (optional)
 *
 * RETURN VALUE
 *   Does not return under normal conditions (calls exit())
 *
 * NOTES
 *   - Prints "exit" message in interactive mode
 *   - No arguments: exits with last command's exit code
 *   - Non-numeric argument: exits with code 2 and error message
 *   - Too many arguments: returns error without exiting
 *   - Numeric argument: exits with specified code (mod 256)
 *   - Frees all allocated memory before exiting
 * ─────────────────────────────────────────────────────────────────────────
 */
int	ft_builtin_exit(t_minishell *msdata, char **args)
{
	int	arg_count;

	if (msdata && msdata->shell_pid == get_shell_pid_from_proc()
		&& isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	arg_count = ft_count_array_elements(args, 0);
	if (arg_count == 0)
		return (ft_handle_no_args(msdata));
	if (!ft_is_numeric(args[0]) || !ft_is_llong(args[0]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit_free_and_exit(msdata, 2);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_exit_code(1);
		return (1);
	}
	return (ft_process_single_arg(msdata, args[0]));
}
