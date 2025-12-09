/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:37:35 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/08 16:37:36 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_line_ready(t_minishell *ms_data);

static void	handle_lexer_error(t_minishell *ms_data, int lexer_result)
{
	if (lexer_result == -1)
	{
		if (isatty(STDIN_FILENO) && ms_data->input_line
			&& ms_data->input_line[0] != '\0')
			add_history(ms_data->input_line);
		ft_exit_code(2);
		if (!isatty(STDIN_FILENO))
		{
			ft_free_shell(ms_data, 0);
			exit(2);
		}
	}
}

static void	process_input_loop(t_minishell *ms_data, int *lexer_result)
{
	while (*lexer_result == 0)
	{
		get_str_readline(ms_data, 2);
		if (ms_data->input_line == NULL)
			break ;
		*lexer_result = ft_lexer(ms_data, ms_data->input_line);
	}
	handle_lexer_error(ms_data, *lexer_result);
}

/*
 * FUNCTION: execute_command
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Executes the parsed command by processing heredocs and running pipeline
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing tokens and parser
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Collects heredoc content before execution
 *   - Only processes non-empty commands
 *   - Coordinates expansion, parsing, and execution phases
 * ─────────────────────────────────────────────────────────────────────────
 */
static void	execute_command(t_minishell *ms_data)
{
	if (ft_collect_heredocs(ms_data) < 0)
	{
		ft_tokens_free(ms_data->tokens);
		ms_data->tokens = NULL;
		return ;
	}
	if (ms_data->input_line && ms_data->input_line[0] != '\0')
		ft_line_ready(ms_data);
}

/*
 * FUNCTION: main
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Main entry point for the minishell program
 *
 * PARAMETERS
 *   ac: Argument count from command line
 *   av: Argument vector from command line
 *   envp: Environment variables from parent process
 *
 * RETURN VALUE
 *   EXIT_SUCCESS on normal termination, other values on error
 *
 * NOTES
 *   - Handles -c flag for command execution without interactive mode
 *   - Initializes shell environment and signal handlers
 *   - Main loop reads input, tokenizes, and executes commands
 *   - Cleans up resources before exit
 * ─────────────────────────────────────────────────────────────────────────
 */
int	main(int ac, char **av, char **envp)
{
	t_minishell	ms_data;
	int			lexer_result;

	if (ac == 3 && ft_strcmp(av[1], "-c") == 0 && av[2])
		return (ft_debug_main_with_c_flag(ac, av, envp));
	ft_init_vars(&ms_data, envp, ac, av);
	shell_struct(&ms_data, 0);
	ft_signals_handle_signals();
	while (1)
	{
		get_str_readline(&ms_data, 1);
		if (ms_data.input_line == NULL)
			ft_builtin_exit(&ms_data, NULL);
		lexer_result = ft_lexer(&ms_data, ms_data.input_line);
		process_input_loop(&ms_data, &lexer_result);
		execute_command(&ms_data);
	}
	return (ft_free_shell(&ms_data, 0), EXIT_SUCCESS);
}
