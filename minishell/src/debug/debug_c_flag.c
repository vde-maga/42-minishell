/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_c_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:29:27 by ruiferna          #+#    #+#             */
/*   Updated: 2025/12/09 09:45:23 by vde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_lexer_error(t_minishell *ms_data, int lexer_result)
{
	if (lexer_result == -1)
		return (-1);
	ft_expander(ms_data, ms_data->env_list);
	if (ms_data->tokens)
	{
		ms_data->parser = ft_parser(ms_data->tokens);
		if (ms_data->parser)
		{
			ft_executor(ms_data, ms_data->parser);
			ft_parser_free(ms_data->parser);
			ms_data->parser = NULL;
		}
		ft_tokens_free(ms_data->tokens);
		ms_data->tokens = NULL;
	}
	return (0);
}

static int	process_c_command(t_minishell *ms_data, char *cmd_str)
{
	int	lexer_result;

	if (!cmd_str || cmd_str[0] == '\0')
		return (0);
	lexer_result = ft_lexer(ms_data, cmd_str);
	while (lexer_result == 0)
	{
		get_str_readline(ms_data, 2);
		if (ms_data->input_line == NULL)
			break ;
		lexer_result = ft_lexer(ms_data, ms_data->input_line);
	}
	return (handle_lexer_error(ms_data, lexer_result));
}

static int	process_commands(t_minishell *ms_data, char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (process_c_command(ms_data, commands[i]) == -1)
			break ;
		i++;
	}
	return (i);
}

int	ft_debug_c_flag(t_minishell *ms_data, char *cmd_string)
{
	char	**commands;
	int		i;

	if (!cmd_string || !ms_data)
		return (1);
	commands = ft_split(cmd_string, ';');
	if (!commands)
	{
		ft_putstr_fd("minishell: -c: memory allocation error\n", 2);
		return (1);
	}
	i = process_commands(ms_data, commands);
	ft_free_str_arrays(commands);
	return (ft_exit_code(i));
}

int	ft_debug_main_with_c_flag(int argc, char **argv, char **envp)
{
	t_minishell	ms_data;
	int			status;

	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
	{
		ft_init_vars(&ms_data, envp, argc, argv);
		status = ft_debug_c_flag(&ms_data, argv[2]);
		ft_free_shell(&ms_data, 0);
		return (status);
	}
	return (1);
}
