#include "minishell.h"

char	*ft_append_char(char *result, char c)
{
	return (ft_string_append(result, &c, APPEND_CHAR));
}

static char	*ft_readline_append(char *line, char c)
{
	return (ft_string_append(line, &c, APPEND_READLINE));
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
