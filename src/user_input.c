#include "../includes/minishell.h"

void get_str_readline(t_minishell *ms_data, int type)
{
    char prompt[PATH_MAX + 32];

    if (ms_data->input_line)
    {
        free(ms_data->input_line);
        ms_data->input_line = NULL;
    }
    if (type == 1)
    {
        ft_get_cwd(ms_data->cwd, sizeof(ms_data->cwd));
        ft_strlcpy(prompt, "minishell$> ", sizeof(prompt));
        ft_strlcat(prompt, ms_data->cwd, sizeof(prompt));
        ft_strlcat(prompt, " > ", sizeof(prompt));
    }
    else if (type == 2)
        ft_strlcpy(prompt, "> ", sizeof(prompt));
    else
        ft_strlcpy(prompt, "", sizeof(prompt));
    ms_data->input_line = readline(prompt);
}
