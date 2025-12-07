#include "../includes/colors.h"
#include "minishell.h"

static void	ft_prompt_clear(char *p)
{
	ft_strlcpy(p, "", PATH_MAX + 32);
}

static void	ft_prompt_append(char *p, const char *s)
{
	ft_strlcat(p, s, PATH_MAX + 32);
}

/*
 * FUNCTION: ft_prompt_print_default
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates and displays the default shell prompt
 *   with colors and current directory
 *
 * PARAMETERS
 *   ms_data: Minishell data structure containing environment and cwd
 *   prompt: Buffer to store the formatted prompt string
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Displays colored "minishell$>" prefix
 *   - Shows shortened current working directory in blue
 *   - Uses tilde (~) for home directory when possible
 *   - Ends with green ">" prompt character
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_prompt_print_default(t_minishell *ms_data, char *prompt)
{
	char	*short_cwd;

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

/*
 * FUNCTION: ft_prompt_print_incomplete
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Creates and displays the continuation prompt for incomplete commands
 *
 * PARAMETERS
 *   prompt: Buffer to store the formatted prompt string
 *
 * RETURN VALUE
 *   None (void function)
 *
 * NOTES
 *   - Shows simple yellow ">" character for line continuation
 *   - Used when command spans multiple lines (unclosed quotes, etc.)
 *   - Minimal design to distinguish from main prompt
 * ─────────────────────────────────────────────────────────────────────────
 */
void	ft_prompt_print_incomplete(char *prompt)
{
	ft_prompt_clear(prompt);
	ft_prompt_append(prompt, RL_YELLOW);
	ft_prompt_append(prompt, ">");
	ft_prompt_append(prompt, RL_RESET);
	ft_prompt_append(prompt, " ");
}
