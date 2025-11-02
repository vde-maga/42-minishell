#include "minishell.h"
#include "../includes/colors.h"

static void ft_prompt_clear(char *p)
{
    ft_strlcpy(p, "", PATH_MAX + 32);
}

static void ft_prompt_append(char *p, const char *s)
{
    ft_strlcat(p, s, PATH_MAX + 32);
}

void	ft_prompt_print_default(t_minishell *ms_data, char *prompt)
{
	char *short_cwd;

	ft_prompt_clear(prompt);
	ft_prompt_append(prompt, RL_BOLD_RED);
	ft_prompt_append(prompt, "minishell$>");
	ft_prompt_append(prompt, RL_RESET);
	ft_prompt_append(prompt, " ");
	ft_prompt_append(prompt, RL_BLUE);
	short_cwd = ft_path_tilde_shorten(ms_data->env_list, ms_data->cwd);
	ft_prompt_append(prompt, short_cwd);
	free(short_cwd);
	ft_prompt_append(prompt, RL_RESET);
	ft_prompt_append(prompt, " ");
	ft_prompt_append(prompt, RL_GREEN);
	ft_prompt_append(prompt, ">");
	ft_prompt_append(prompt, RL_RESET);
	ft_prompt_append(prompt, " ");
}

void	ft_prompt_print_incomplete(char *prompt)
{
	ft_prompt_clear(prompt);
	ft_prompt_append(prompt, RL_YELLOW);
	ft_prompt_append(prompt, ">");
	ft_prompt_append(prompt, RL_RESET);
	ft_prompt_append(prompt, " ");
}