#include <minishell.h>

/** 
* @brief Frees the memory of an array of strings (char **).
* @param str The array of strings to be freed.
*/
void	ft_free_str_arrays(char **str)
{
	int	i;

	if (!str)
		return;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free (str);
}
/** 
* @brief Frees all dynamically allocated memory in the struct t_minishell.
* @param ms_data A pointer to the struct t_minishell to be cleaned up.
* 
* This function is designed to be safe:
* 1. Checks that the pointer to the main struct is null.
* 2. Frees the ‘env’ string array safely.
* 3. Frees the ‘input_line’ and ‘input’ strings, checking that they are not null.
* 4. Does NOT attempt to free ‘cwd’ because it is a static array in the struct.
* 5. Zeroes the pointers after freeing them to avoid dangling pointers.
*/
void	ft_free_shell(t_minishell *ms_data)
{
	if (!ms_data)
		return;
	if (ms_data->env)
	{
		ft_free_str_arrays(ms_data->env);
		ms_data->env = NULL;
	}
	if (ms_data->input_line)
	{
		free(ms_data->input_line);
		ms_data->input_line = NULL;
	}
	if (ms_data->input)
	{
		free(ms_data->input);
		ms_data->input = NULL;
	}
}