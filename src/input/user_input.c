#include "../includes/minishell.h"

void get_str_readline(t_minishell *ms_data, int type)
{
    char prompt[PATH_MAX + 32];
    char *old_ref;
    char *line;
    char *trimmed;

    ft_usr_print_prompt_color(ms_data, type, prompt);

    /*      CODE JUST FOR MSTEST        */
    if (!isatty(fileno(stdin)))
    {
        line = get_next_line(fileno(stdin));
        if (!line)
        {
            /* EOF */
            free(ms_data->input_line);
            ms_data->input_line = NULL;
            return;
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
        return;
    }
    /*      END CODE JUST FOR MSTEST        */

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
