#include "../includes/minishell.h"

char *get_str_readline(int type)
{
    char    *buffer;
    size_t  buffsize;
    char    cwd[BUFSIZ];

    buffer = NULL;
    if (type == 1)
    {
        ft_get_cwd(cwd, sizeof(cwd));
        ft_printf("minishell$> %s > ", cwd);
    }
    else
        ft_printf("> ");
    if (getline(&buffer, &buffsize, stdin) == -1)
    {
        buffer = NULL;
        if (feof(stdin))
            // TODO: Need to remove the use of `feof` function.
            //       This if is triggered when you use Ctrl + D (for example)
            ft_printf("[EOF]");
        else
            ft_printf("getline func failed!");
    }
    return (buffer);
}
