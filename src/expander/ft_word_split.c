#include "minishell.h"

static int	ft_count_words(char *str)
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

static char	*ft_extract_word(char *str, int *pos)
{
	int		start;
	int		len;
	char	*word;

	while (str[*pos] && (str[*pos] == ' '
			|| str[*pos] == '\t' || str[*pos] == '\n'))
		(*pos)++;
	start = *pos;
	len = 0;
	while (str[*pos] && str[*pos] != ' '
		&& str[*pos] != '\t' && str[*pos] != '\n')
	{
		(*pos)++;
		len++;
	}
	word = ft_substr(str, start, len);
	return (word);
}

char	**ft_word_split(char *str)
{
	char	**words;
	int		count;
	int		i;
	int		pos;

	if (!str || !*str)
		return (NULL);
	count = ft_count_words(str);
	if (count == 0)
		return (NULL);
	words = ft_calloc(count + 1, sizeof(char *));
	if (!words)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < count)
	{
		words[i] = ft_extract_word(str, &pos);
		if (!words[i])
		{
			while (--i >= 0)
				free(words[i]);
			return (free(words), NULL);
		}
		i++;
	}
	return (words);
}
