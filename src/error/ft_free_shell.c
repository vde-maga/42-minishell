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

void	ft_free_shell(t_minishell *ms_data)
{
	if (!ms_data)
		return ;
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
	ft_free_env_list(ms_data->env_list);
}

void	ft_free_shell_child(t_minishell *ms_data)
{
	if (!ms_data)
		return ;
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
	if (ms_data->env_list)
		ft_free_env_list(ms_data->env_list);
	if (ms_data->tokens)
		ft_tokens_free(ms_data->tokens);
	if (ms_data->parser)
		ft_parser_free(ms_data->parser);
}
