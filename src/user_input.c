#include "../includes/minishell.h"

void get_str_readline(t_minishell *ms_data, int type)
{
    char prompt[PATH_MAX + 32];
    char *old_ref;

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
    if (type == 2)
    {
        old_ref = ms_data->input_line;
        ms_data->input_line = ft_strjoin(old_ref, readline(prompt));
        free(old_ref);
    }
    else
        ms_data->input_line = readline(prompt);
}
