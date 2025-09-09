# include "../includes/minishell.h"

void    ft_get_cwd(char *buffer, size_t size)
{
    if (getcwd(buffer, size) == NULL)
        perror("getcwd failed");
    /*
         I think that the advantage of be using "wrappers" around allowed
         functions is to better handle the errors independently from main.
         I think that this method is better to handle the expected exit codes
    */
    // TODO: Handle exit codes
    // exit(1) or t_minishell->exit_code = 1
}