#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int	ft_count_array_elements(char **array, char delimiter)
{
	int	count;

	count = 0;
	if (!array && !delimiter)
		return (0);
	if (array)
	{
		while (array && array[count])
			count++;
	}
	else if (delimiter)
	{
		return (0);
	}
	return (count);
}

static char	*handle_null_original(char *to_append, int append_mode)
{
	char	*result;

	if (append_mode == APPEND_CHAR)
	{
		result = malloc(2);
		if (result)
		{
			result[0] = *((char *)to_append);
			result[1] = '\0';
		}
		return (result);
	}
	else if (append_mode == APPEND_STRING)
		return (ft_strdup(to_append));
	else
		return (NULL);
}

static char	*append_char_mode(char *original, char *to_append)
{
	char	*result;
	size_t	len;

	len = ft_strlen(original);
	result = malloc(len + 2);
	if (!result)
		return (free(original), NULL);
	ft_memcpy(result, original, len);
	result[len] = *((char *)to_append);
	result[len + 1] = '\0';
	return (result);
}

static char	*append_string_mode(char *original, char *to_append)
{
	char	*result;
	size_t	len;
	size_t	append_len;

	len = ft_strlen(original);
	append_len = ft_strlen(to_append);
	result = malloc(len + append_len + 1);
	if (!result)
		return (free(original), NULL);
	ft_memcpy(result, original, len);
	ft_memcpy(result + len, to_append, append_len);
	result[len + append_len] = '\0';
	return (result);
}

char	*ft_string_append(char *original, char *to_append, int append_mode)
{
	char	*result;

	if (!to_append && append_mode != APPEND_CHAR)
		return (original);
	if (!original)
		return (handle_null_original(to_append, append_mode));
	if (append_mode == APPEND_CHAR)
		result = append_char_mode(original, to_append);
	else if (append_mode == APPEND_STRING)
		result = append_string_mode(original, to_append);
	else
		result = append_char_mode(original, to_append);
	free(original);
	return (result);
}
