#include "../includes/minishell.h"

void	ft_line_ready(t_minishell *ms_data);

void	ft_line_ready(t_minishell *ms_data)
{
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
	add_history(ms_data->input_line);
}
