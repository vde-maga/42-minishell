#include <minishell.h>

void	ft_free_str_arrays(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_shell_data(t_minishell *ms_data)
{
	if (ms_data->env)
	{
		ft_free_str_arrays(ms_data->env);
		ms_data->env = NULL;
	}
	if (ms_data->input_line)
	{
		free(ms_data->input_line);
		ms_data->input_line = NULL;
	}
	if (ms_data->input)
	{
		free(ms_data->input);
		ms_data->input = NULL;
	}
}

void	ft_close_shell_fds(t_minishell *ms_data)
{
	if (ms_data->hdc_fds[0] != -1)
		close(ms_data->hdc_fds[0]);
	if (ms_data->hdc_fds[1] != -1)
		close(ms_data->hdc_fds[1]);
	if (ms_data->saved_stdin != -1)
		close(ms_data->saved_stdin);
	if (ms_data->saved_stdout != -1)
		close(ms_data->saved_stdout);
}

void	ft_free_child_resources(t_minishell *ms_data)
{
	if (ms_data->tokens)
		ft_tokens_free(ms_data->tokens);
	if (ms_data->parser)
		ft_parser_free(ms_data->parser);
}
