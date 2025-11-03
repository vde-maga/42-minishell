#include "../../includes/minishell.h"

static void	process_c_command(t_minishell *ms_data, char *cmd_str)
{
	int	lexer_result;

	if (!cmd_str || cmd_str[0] == '\0')
		return ;
	lexer_result = ft_lexer(ms_data, cmd_str);
	while (lexer_result == 0)
	{
		get_str_readline(ms_data, 2);
		if (ms_data->input_line == NULL)
			break ;
		lexer_result = ft_lexer(ms_data, ms_data->input_line);
	}
	if (lexer_result == -1)
		return ;
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
	i = 0;
	while (commands[i])
	{
		process_c_command(ms_data, commands[i]);
		i++;
	}
	ft_free_str_arrays(commands);
	return (ft_exit_code(-1));
}

int	ft_debug_main_with_c_flag(int argc, char **argv, char **envp)
{
	t_minishell	ms_data;
	int			status;

	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
	{
		ft_init_vars(&ms_data, envp);
		status = ft_debug_c_flag(&ms_data, argv[2]);
		ft_free_shell(&ms_data);
		return (status);
	}
	return (1);
}
