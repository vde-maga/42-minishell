#include "../includes/minishell.h"

void get_str_readline(t_minishell *ms_data, int type)
{
    char prompt[PATH_MAX + 32];
    char *old_ref;

    ft_usr_print_prompt_color(ms_data, type, prompt);
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
