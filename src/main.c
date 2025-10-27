#include "../includes/minishell.h"

void ft_line_ready(t_minishell *ms_data);

int main(int ac, char **av, char **envp)
{
	t_minishell	ms_data;

	(void)ac;
	(void)av;
	ft_init_vars(&ms_data, envp);
	ft_signal_handle_signals();
	while (1)
	{
		int lexer_result;

		get_str_readline(&ms_data, 1);
		if (ms_data.input_line == NULL)
			ft_builtin_exit(&ms_data, NULL);
		lexer_result = ft_lexer(&ms_data, ms_data.input_line);
		while (lexer_result == 0)
		{
				get_str_readline(&ms_data, 2);
				if (ms_data.input_line == NULL)
					break;
				lexer_result = ft_lexer(&ms_data, ms_data.input_line);
		}
		if (lexer_result == -1)
			continue;
		if (ms_data.input_line && ms_data.input_line[0] != '\0')
			ft_line_ready(&ms_data);
    }
	ft_free_shell(&ms_data);
    return (EXIT_SUCCESS);
}

void ft_line_ready(t_minishell *ms_data)
{
	// ft_test_heredoc(ms_data);
	// print_tokens(ms_data->tokens);
	ft_expander(ms_data, ms_data->env_list);
	if (ms_data->tokens)
	{
		ms_data->parser = ft_parser(ms_data->tokens);
		if (ms_data->parser)
		{
			// ft_parser_tree_test(ms_data->parser);
			ft_executor(ms_data, ms_data->parser);
			ft_parser_free(ms_data->parser);
			ms_data->parser = NULL;
		}
		ft_tokens_free(ms_data->tokens);
		ms_data->tokens = NULL;
	}
	add_history(ms_data->input_line);
}
