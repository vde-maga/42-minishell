#include "minishell.h"

int	is_valid_env_var_name(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!( (str[i] >= 'A' && str[i] <= 'Z') || 
			   (str[i] >= 'a' && str[i] <= 'z') || 
			   str[i] == '_' || 
			   (i > 0 && (str[i] >= '0' && str[i] <= '9')) ))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_special_param(char *str)
{
	if (!str || !*str)
		return (0);
	
	if ((str[0] == '?' || str[0] == '$') && str[1] == '\0')
		return (1);
	return (0);
}

int get_shell_pid_from_proc(void)
{
	ssize_t bytes_read;
	char buffer[256];
    int fd;
	int pid;

	fd = open("/proc/self/stat", O_RDONLY);
    if (fd == -1)
        return -1;
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);
    if (bytes_read <= 0)
        return -1;
    buffer[bytes_read] = '\0';
    pid = ft_atoi(buffer);
    return (pid);
}
