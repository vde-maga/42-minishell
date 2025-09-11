#include "minishell.h"

int	ft_input_validation(t_minishell *ms_data)
{
	if (ms_data->input_line[0] == '\0')
		return (1);
	ms_data->input = ft_strtrim(ms_data->input, "\t ");
	if (!ms_data->input)
		ft_exit_failure(ms_data, "Input Validation");
	if (ms_data->input[0] == '\0')
		return (1);
	return (0);
}
