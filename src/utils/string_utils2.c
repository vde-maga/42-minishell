#include "minishell.h"

int	ft_count_words(char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_isprint_byte(int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	return (uc >= 32 && uc != 127);
}
