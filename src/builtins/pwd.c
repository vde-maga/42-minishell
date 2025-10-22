#include "minishell.h"

int	ft_builtin_pwd(void)
{
	char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("pwd"), 1);
    ft_printf("%s\n", cwd);
    free(cwd);
    return (0);
}
