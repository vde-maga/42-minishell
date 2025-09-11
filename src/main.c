#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_minishell	ms_data;

	(void)ac;
	(void)av;
	(void)envp;
	ft_init_vars(&ms_data);
	while (1)
	{
		ms_data->input_line = readline(ms_data->cwd);
		if (ms_data->input_line && ms_data->input_line[0] != '\0')
			add_history(ms_data->input_line);
		if (ms_data->input_line && ft_input_validation(ms_data));
		{
			ft_free_minishell(ms_data);
			continue;
		}
		printf("%s", line);
		if (!line)
			break;
    
		// TODO: 2 - Tokenize the input (Lexing)

		// TODO: 3 - Parsing -> Evaluating -> Exec and repeat
	}
	return (EXIT_SUCCESS);
}
