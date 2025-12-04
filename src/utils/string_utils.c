#include "minishell.h"
#include "lexer.h"
#include "parser.h"

// Unified function to count elements in arrays or words in strings
int	ft_count_array_elements(char **array, char delimiter)
{
	int	count;

	count = 0;
	if (!array && !delimiter)
		return (0);
	if (array)
	{
		// Count NULL-terminated array elements
		while (array && array[count])
			count++;
	}
	else if (delimiter)
	{
		// This case would be for string counting, but we'll keep the original
		// ft_count_words function for string-specific logic
		return (0);
	}
	return (count);
}

// Generic linked list freeing function
void	ft_free_linked_list(void *list, void (*free_func)(void *))
{
	void	*current;
	void	*next;

	if (!list || !free_func)
		return ;
	current = list;
	while (current)
	{
		// Cast to appropriate struct types to get next field
		if (free_func == ft_free_token_node)
			next = ((t_token *)current)->next;
		else if (free_func == ft_free_redir_node)
			next = ((t_redir *)current)->next;
		else
			next = ((void **)current)[0]; // Fallback for other types
		free_func(current);
		current = next;
	}
}

// Specific free functions for tokens and redirections
void	ft_free_token_node(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	if (!t)
		return ;
	if (t->value)
		free(t->value);
	if (t->heredoc_content)
		free(t->heredoc_content);
	free(t);
}

void	ft_free_redir_node(void *redir)
{
	t_redir	*r;

	r = (t_redir *)redir;
	if (!r)
		return ;
	if (r->filename)
		free(r->filename);
	if (r->heredoc_content)
		free(r->heredoc_content);
	free(r);
}

// Unified string building function with different append modes
char	*ft_string_append(char *original, char *to_append, int append_mode)
{
	char	*result;
	size_t	len;
	size_t	append_len;

	if (!to_append && append_mode != APPEND_CHAR)
		return (original);
	if (!original)
	{
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
	len = ft_strlen(original);
	if (append_mode == APPEND_CHAR)
	{
		result = malloc(len + 2);
		if (!result)
			return (free(original), NULL);
		ft_memcpy(result, original, len);
		result[len] = *((char *)to_append);
		result[len + 1] = '\0';
	}
	else if (append_mode == APPEND_STRING)
	{
		append_len = ft_strlen(to_append);
		result = malloc(len + append_len + 1);
		if (!result)
			return (free(original), NULL);
		ft_memcpy(result, original, len);
		ft_memcpy(result + len, to_append, append_len);
		result[len + append_len] = '\0';
	}
	else // APPEND_READLINE
	{
		result = malloc(len + 2);
		if (!result)
			return (free(original), NULL);
		ft_memcpy(result, original, len);
		result[len] = *((char *)to_append);
		result[len + 1] = '\0';
	}
	free(original);
	return (result);
}

// Keep the original word counting function for string-specific logic
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
