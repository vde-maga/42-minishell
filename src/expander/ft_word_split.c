#include "minishell.h"

// ft_count_words is now implemented in utils/string_utils.c

/*
 * FUNCTION: ft_extract_word
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Extract next word from string starting at given position
 *
 * PARAMETERS
 *   @str: Source string to extract word from
 *   @pos: Position pointer (updated to after extracted word)
 *
 * RETURN VALUE
 *   Newly allocated word string, or NULL on allocation failure
 *
 * NOTES
 *   - Skips leading whitespace before extraction
 *   - Updates position pointer to point after extracted word
 *   - Memory allocation responsibility: caller must free returned string
 * ─────────────────────────────────────────────────────────────────────────
 */
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

/*
 * FUNCTION: fill_words
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Fill word array by extracting words from string
 *
 * PARAMETERS
 *   @words: Pre-allocated array to fill with word strings
 *   @str: Source string to extract words from
 *   @count: Number of words to extract
 *
 * RETURN VALUE
 *   0 on success, -1 on memory allocation failure
 *
 * NOTES
 *   - Cleans up allocated memory on failure
 *   - Uses position pointer to track extraction progress
 *   - Memory allocation responsibility: function manages word string allocation
 * ─────────────────────────────────────────────────────────────────────────
 */
static int	fill_words(char **words, char *str, int count)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < count)
	{
		words[i] = ft_extract_word(str, &pos);
		if (!words[i])
		{
			while (--i >= 0)
				free(words[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

/*
 * FUNCTION: ft_word_split
 * ─────────────────────────────────────────────────────────────────────────
 * PURPOSE
 *   Split a string into words based on whitespace delimiters
 *
 * PARAMETERS
 *   @str: String to split into words
 *
 * RETURN VALUE
 *   Array of word strings, or NULL on error/empty input
 *
 * NOTES
 *   - Uses space, tab, and newline as delimiters
 *   - Returns NULL-terminated array of strings
 *   - Memory allocation responsibility: caller must free array and strings
 * ─────────────────────────────────────────────────────────────────────────
 */
char	**ft_word_split(char *str)
{
	char	**words;
	int		count;

	if (!str || !*str)
		return (NULL);
	count = ft_count_words(str);
	if (count == 0)
		return (NULL);
	words = ft_calloc(count + 1, sizeof(char *));
	if (!words)
		return (NULL);
	if (fill_words(words, str, count) < 0)
		return (free(words), NULL);
	return (words);
}
