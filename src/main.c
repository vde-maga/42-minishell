#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_minishell	ms_data;
	char *old;

	(void)ac;
	(void)av;
	(void)envp;
	ft_init_vars(&ms_data);
	while (1)
	{
		get_str_readline(&ms_data, 1);
		if (ms_data.input_line == NULL)
			break;
        while (ft_lexer(ms_data.input_line) == 0)
        {
			old = ft_strdup(ms_data.input_line);
			get_str_readline(&ms_data, 2);
			if (ms_data.input_line == NULL)
				break;
            ms_data.input_line = ft_strjoin(old, ms_data.input_line);
        }
		if (ms_data.input_line && ms_data.input_line[0] != '\0')
		{
			ft_test_heredoc(&ms_data);
			add_history(ms_data.input_line);
		}

		// TODO: 3 - Parsing -> Evaluating -> Exec and repeat
    }
	ft_free_shell(&ms_data);
    return EXIT_SUCCESS;
}
