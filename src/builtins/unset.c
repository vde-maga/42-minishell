#include "minishell.h"

int	ft_builtin_unset(t_minishell *msdata, char *key)
{
	if (!key || !msdata)
		return (1);
	return (ft_unset_env_var(&msdata->env_list, key));
}
