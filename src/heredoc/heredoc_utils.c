#include "minishell.h"

char	*ft_append_var(t_minishell *ms_data, char *result,
	char *line, int *i)
{
	char	*var_value;
	char	*temp;
	int		var_len;

	var_len = ft_get_var_name_len(&line[*i + 1]);
	var_value = ft_get_var_value(ms_data, &line[*i + 1], var_len);
	temp = result;
	result = ft_strjoin(result, var_value);
	free(temp);
	free(var_value);
	*i += var_len + 1;
	return (result);
}

char	*ft_append_char(char *result, char c)
{
	char	char_str[2];
	char	*temp;

	char_str[0] = c;
	char_str[1] = '\0';
	temp = result;
	result = ft_strjoin(result, char_str);
	free(temp);
	return (result);
}

static char	*ft_readline_append(char *line, char c)
{
	char	*new_line;
	size_t	len;

	if (!line)
	{
		new_line = malloc(2);
		if (!new_line)
			return (NULL);
		new_line[0] = c;
		new_line[1] = '\0';
		return (new_line);
	}
	len = ft_strlen(line);
	new_line = malloc(len + 2);
	if (!new_line)
		return (free(line), NULL);
	ft_memcpy(new_line, line, len);
	new_line[len] = c;
	new_line[len + 1] = '\0';
	free(line);
	return (new_line);
}

char	*ft_heredoc_readline(int fd)
{
	char	*line;
	char	c;
	ssize_t	bytes_read;

	line = NULL;
	while (1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				return (free(line), NULL);
			return (line);
		}
		if (c == '\n')
			return (ft_readline_append(line, c));
		line = ft_readline_append(line, c);
		if (!line)
			return (NULL);
	}
}
