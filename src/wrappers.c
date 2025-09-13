# include "../includes/minishell.h"

void    ft_get_cwd(char *buffer, size_t size)
{
    if (getcwd(buffer, size) == NULL)
    {
        perror("getcwd failed");
        // Optionally, handle error: exit(1) or set error code
    }
}