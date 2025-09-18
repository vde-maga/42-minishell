#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_minishell	ms_data;
	// char *old;

	(void)ac;
	(void)av;
	ft_init_vars(&ms_data);
	ms_data.env_list = ft_get_env_list(envp);
	if (!ms_data.env_list)
	{
		ft_printf("Algum Erro na Coleta da ENV");
		return (1);
	}
	while (1)
	{
		get_str_readline(&ms_data, 1);
		if (ms_data.input_line == NULL)
			break;
		while (ft_lexer(&ms_data, ms_data.input_line) == 0)
		{
				get_str_readline(&ms_data, 2);
				if (ms_data.input_line == NULL)
					break;
		}
		if (ms_data.input_line && ms_data.input_line[0] != '\0')
		{
//			ft_expander(ft_lexer_tokens(ms_data.input_line), ms_data.env_list);
			// print_tokens(ft_expander(ft_lexer_tokens(ms_data.input_line), ms_data.env_list));
			// ft_test_heredoc(&ms_data);
			// tokens = ft_lexer_tokens(ms_data.input_line);
			ft_expander(ms_data.tokens, ms_data.env_list);
			if (ms_data.tokens)
			{
				ft_parser_test(ms_data.tokens);
				ft_tokens_free(ms_data.tokens);
				ms_data.tokens = NULL;
			}
			add_history(ms_data.input_line);
		}

		// TODO: 3 - Parsing -> Evaluating -> Exec and repeat
    }
	ft_free_shell(&ms_data);
    return (EXIT_SUCCESS);
}

