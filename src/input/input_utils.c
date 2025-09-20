#include "minishell.h"

void    ft_usr_print_prompt(t_minishell *ms_data, int type, char *prompt)
{
    if (type == 1)
    {
        ft_get_cwd(ms_data->cwd, sizeof(ms_data->cwd));
        ft_strlcpy(prompt, "minishell$> ", PATH_MAX+32);
        ft_strlcat(prompt, ms_data->cwd, PATH_MAX+32);
        ft_strlcat(prompt, " > ", PATH_MAX+32);
    }
    else if (type == 2)
        ft_strlcpy(prompt, "> ", PATH_MAX+32);
    else
        ft_strlcpy(prompt, "", PATH_MAX+32);
}

void    ft_usr_print_prompt_color(t_minishell *ms_data, int type, char *prompt)
{
    if (type == 1)
    {
        ft_get_cwd(ms_data->cwd, sizeof(ms_data->cwd));
        ft_prompt_print_default(ms_data, prompt);
    }
    else if (type == 2)
        ft_prompt_print_incomplete(prompt);
    else
        ft_strlcpy(prompt, "", PATH_MAX+32);
}