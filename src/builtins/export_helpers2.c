#include "minishell.h"

int	ft_calculate_allocate_space(char *value)
{
	int	i;
	int	count_allocate_space;

	i = 0;
	count_allocate_space = 0;
	while (value[i])
	{
		if (value[i] == ' ')
		{
			count_allocate_space++;
			while (value[i] == ' ')
				i++;
		}
		else
		{
			count_allocate_space++;
			i++;
		}
	}
	return (count_allocate_space);
}

char	*ft_remove_spaces(char *value)
{
	int		i;
	int		j;
	char	*new_value;

	new_value = (char *)malloc(ft_calculate_allocate_space(value) + 1);
	if (!new_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		new_value[j++] = value[i];
		if (value[i] == ' ')
			while (value[i] == ' ')
				i++;
		else
			i++;
	}
	new_value[j] = '\0';
	free(value);
	return (new_value);
}
