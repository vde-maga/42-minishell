#include "minishell.h"

static void	handle_char(t_qctx *c)
{
	if (c->s[c->i] == '\'' && c->mode != 2)
	{
		if (c->mode == 1)
			c->mode = 0;
		else
			c->mode = 1;
		c->i++;
	}
	else if (c->s[c->i] == '"' && c->mode != 1)
	{
		if (c->mode == 2)
			c->mode = 0;
		else
			c->mode = 2;
		c->i++;
	}
	else
		c->d[c->j++] = c->s[c->i++];
}

static int	fill_without_quotes(const char *str, char *dest, int *mode)
{
	t_qctx			c;

	c.s = str;
	c.d = dest;
	c.i = 0;
	c.j = 0;
	c.mode = 0;
	while (c.s[c.i])
		handle_char(&c);
	dest[c.j] = '\0';
	*mode = c.mode;
	return (c.j);
}

char	*ft_remove_quotes(char *str)
{
	char			*dest;
	int				mode;
	int				j;

	if (!str)
		return (NULL);
	dest = (char *)malloc(ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	j = fill_without_quotes(str, dest, &mode);
	if (mode != 0 || j == (int)ft_strlen(str))
	{
		free(dest);
		return (ft_strdup(str));
	}
	return (dest);
}

int	ft_exp_replace_content(t_env *env, t_token *current, char *var_name)
{
	char		*new_value;
	char		*old_value;
	t_env		*env_node;

	env_node = ft_get_env_var(env, var_name);
	if (env_node && env_node->value)
		new_value = ft_strdup(env_node->value);
	else
		new_value = ft_strdup("");
	if (!new_value)
		return (-1);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}

int	ft_exp_special_param(t_minishell *msdata, t_token *current, char *var_name)
{
	char		*new_value;
	char		*old_value;

	(void)var_name;
	(void)msdata;
	if (ft_strcmp(current->value, "$$") == 0)
		new_value = ft_itoa(get_shell_pid_from_proc());
	else if (ft_strcmp(current->value, "$?") == 0)
		new_value = ft_itoa(ft_exit_code(-1));
	else
		new_value = ft_itoa(42);
	old_value = current->value;
	current->value = new_value;
	free(old_value);
	return (0);
}
