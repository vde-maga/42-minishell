#include "../includes/minishell.h"

void	ft_cleanup_gnl_buffer(int fd)
{
	char	*line;

	(void)fd;
	if (isatty(STDIN_FILENO))
		return ;
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		free(line);
	}
}

static void	get_str_non_interactive(t_minishell *ms_data, int type)
{
	char	*line;
	char	*trimmed;
	char	*old_ref;

	line = get_next_line(STDIN_FILENO);
	if (!line)
	{
		free(ms_data->input_line);
		ms_data->input_line = NULL;
		return ;
	}
	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (type == 2)
	{
		old_ref = ms_data->input_line;
		ms_data->input_line = ft_strjoin(old_ref, trimmed);
		free(old_ref);
		free(trimmed);
	}
	else
	{
		free(ms_data->input_line);
		ms_data->input_line = trimmed;
	}
}

void	get_str_readline(t_minishell *ms_data, int type)
{
	char	prompt[PATH_MAX + 32];
	char	*old_ref;

	ft_usr_print_prompt_color(ms_data, type, prompt);
	if (!isatty(STDIN_FILENO))
	{
		get_str_non_interactive(ms_data, type);
		return ;
	}
	if (type == 2)
	{
		old_ref = ms_data->input_line;
		ms_data->input_line = ft_strjoin(old_ref, readline(prompt));
		free(old_ref);
	}
	else
	{
		free(ms_data->input_line);
		ms_data->input_line = readline(prompt);
	}
}
