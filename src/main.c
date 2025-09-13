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
        while (ft_lexer(ms_data.input_line) == 0)
        {
			old = ft_strdup(ms_data.input_line);
			get_str_readline(&ms_data, 2);
            ms_data.input_line = ft_strjoin(old, ms_data.input_line);
        }
		if (ms_data.input_line && ms_data.input_line[0] != '\0')
			add_history(ms_data.input_line);
        
        // TODO: 3 - Parsing -> Evaluating -> Exec and repeat
    }
	free(old);
    return EXIT_SUCCESS;
}
